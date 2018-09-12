package com.kalah46.logic;

import java.util.Collections;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;

import com.kalah46.types.Farm;
import com.kalah46.types.House;
import com.kalah46.types.Seed;
import com.kalah46.types.SeedContainer;
import com.kalah46.types.Store;
import com.kalah46.types.playerSide;

public class TUI {
    public int      numPits;
    private int     time;
    private Scanner inputScanner = new Scanner(System.in);
    
    public Farm[] playerLand;
    private int   maxTurns;
    private int   MAXMOVES;

    public String boardToString() {
        String result = new String();
        String line1 = new String();
        String line2 = new String();
        {
            
            playerSide side = playerSide.back;
            
            result += "Player " + Integer.toString(side.toInt() + 1) + " "
                      + side.toString() + "\n";
            
            line1 += "R";
            line2 += Integer.toString(
                this.playerLand[side.toInt()].resourcePool.countPebble()
            );
            for (int i = this.numPits - 1; i >= 0; i--) {
                line1 += " | " + Integer.toString(i);
                line2 += "   "
                         + Integer.toString(this.getPit(side, i).countPebble());
            }
            result += line1 + "\n" + line2 + "\n";
        }
        {
            line1 = new String();
            line2 = new String();
            playerSide side = playerSide.front;
            result += "Player " + Integer.toString(side.toInt() + 1) + " "
                      + side.toString() + "\n";
            for (int i = 0; i <= (this.numPits - 1); i++) {
                line1 += Integer.toString(i) + " | ";
                line2 += Integer.toString(this.getPit(side, i).countPebble())
                         + "   ";
                
            }
            
            line1 += "R";
            line2 += Integer.toString(
                this.playerLand[side.ordinal()].resourcePool.countPebble()
            );
            result += line1 + "\n" + line2 + "\n";
        }
        
        return result;
    }
    
    // display board status
    public void displayBoard() {
        System.out.println(this.boardToString());
    }

    // evaluate winning state
    public void evaluateResult(Farm[] playerLand, playerSide thisPlayer) {
        int thisPlayerPebbles =
            playerLand[thisPlayer.toInt()].resourcePool.countPebble();
        int opponentPlayerPebbles = playerLand[this.getOppositeSide(
            thisPlayer
        ).toInt()].resourcePool.countPebble();
        if (thisPlayerPebbles > opponentPlayerPebbles) {
            System.out.println(thisPlayer + " win!");
        } else if (thisPlayerPebbles < opponentPlayerPebbles) {
            System.out.println(this.getOppositeSide(thisPlayer) + " win!");
        } else {
            System.out.println("It's a tie!");
        }
    }

    // get the opposite pit's column number
    protected int getOppositeColumn(int column) {
        return (this.numPits - 1 - column);
    }

    // change player side
    protected playerSide getOppositeSide(playerSide side) {
        return playerSide.values()[(1 - side.ordinal())];
    }
    
    // pick a pit given the side and column
    protected House getPit(playerSide side, int column) {
        return this.playerLand[side.ordinal()].pits.get(column);
    }
    
    // pick the resource pool on the given side
    protected Store getResourcePool(playerSide side) {
        return this.playerLand[side.ordinal()].resourcePool;
    }

    // move pebble from the pit player picked
    public Boolean movePebble(final playerSide thisPlayer, int column) {
        playerSide currentSide = thisPlayer;
        SeedContainer pickedPit = this.getPit(thisPlayer, column);
        // PebbleContainer previousPit;
        final Farm ourLand = this.playerLand[thisPlayer.ordinal()];
        
        // INVALID MOVE
        if (pickedPit.countPebble() == 0) {
            System.out.println("Warning: can't pick an empty pit");
        }
        
        Vector<Integer> pebbles = pickedPit.clearPebble();
        final int numPebbles = pebbles.size();
        for (int i = 0; i < numPebbles; i++) {
            // previousPit = pickedPit;
            if (pickedPit == ourLand.resourcePool) {
                // Place into first enemy pit
                column = 0;
                currentSide = this.getOppositeSide(currentSide);
                pickedPit = this.getPit(currentSide, column);
            } else {
                // check if it is the last pit on the side
                if (column == (this.numPits - 1)) {
                    // check if it is on the player's side
                    if (currentSide == thisPlayer) {
                        // column=-1;
                        pickedPit = ourLand.resourcePool;
                    } else {
                        column = 0;
                        currentSide = thisPlayer;
                        pickedPit = this.getPit(currentSide, column);
                    }
                } else {
                    column++;
                    pickedPit = this.getPit(currentSide, column);
                }
            }
            pickedPit.addPebble(pebbles.remove(0));
        }
        Boolean playAgain =
            (pickedPit == this.playerLand[thisPlayer.ordinal()].resourcePool);
        if (
            (pickedPit.countPebble() == 1) && (currentSide == thisPlayer)
            && !playAgain
        ) {
            pebbles = this.getPit(
                this.getOppositeSide(currentSide), this.getOppositeColumn(column)
            ).clearPebble();
            pebbles.addAll(this.getPit(currentSide, column).clearPebble());
            ourLand.resourcePool.addAllPebbles(pebbles);
        }
        // check if all pits on one side is empty, if it is, end the game
        if (
            this.playerLand[thisPlayer.ordinal()].pits.isEmpty()
            || this.playerLand[this.getOppositeSide(thisPlayer).ordinal()].pits.isEmpty()
        ) {
            System.out.println("Game ends");
            this.evaluateResult(this.playerLand, thisPlayer);
            return false;
        }

        return playAgain; // return true if the player have another turn
    }

    // parse an input command and move pebble from the specified pit
    public boolean movePebble(int side, int column) {
        this.maxTurns++;

        // INVALID MOVE
        if ((column < 0) || (column >= this.numPits)) {
            System.out.println("Warning: pit doesn't exist");
        }

        playerSide thisPlayer = playerSide.values()[side];
        Farm ourLand = this.playerLand[thisPlayer.toInt()];
        Farm opponentLand = this.playerLand[thisPlayer.oppositeI()];

        // check maximum moves reached or not
        if (this.maxTurns != this.MAXMOVES) {
            // player move pebble
            boolean secondChance = this.movePebble(thisPlayer, column);
            
            // check whether one player's pits are empty
            if (
                ourLand.checkEmpty(ourLand, this.numPits)
                || opponentLand.checkEmpty(opponentLand, this.numPits)
            ) {
                System.out.println("Game ends");
                this.evaluateResult(this.playerLand, thisPlayer);
                return false;
            }
            return secondChance;
        } else {
            System.out.println("Game ends(You have reached the maximum moves)");
            this.evaluateResult(this.playerLand, thisPlayer);
            return false;
        }
    }

    public Vector<Integer> random(int count, int sum) {
        Random r = new Random();
        Vector<Integer> vals = new Vector<>();
        sum -= count;
        
        for (int i = 0; i < (count - 1); i++) {
            vals.add(i, r.nextInt(sum));
        }
        vals.add(count - 1, sum);
        
        Collections.sort(vals);
        for (int i = count - 1; i > 0; i--) {
            vals.set(i, vals.get(i) - vals.get(i - 1));
        }
        for (int i = 0; i < count; ++i) {
            vals.set(i, vals.get(i) + 1);
        }
        return vals;
    }
    
    // reset board state
    public void resetBoard(Vector<Integer> numPebbles) {
        this.MAXMOVES = 100;
        this.maxTurns = 100;
        int length = playerSide.values().length;
        this.playerLand = new Farm[length];
        for (int i = 0; i < length; i++) {
            this.playerLand[i] = new Farm(this.numPits, numPebbles);
        }
    }
    
    // ready, start!
    public void start(String[] args) {
        System.out.println(
            "Configure your game, input number of House (4 to 9) for each player: "
        );
        String inputNumPits = this.inputScanner.nextLine();
        this.numPits = Integer.parseInt(inputNumPits);
        
        final int avgNumPebbles;
        System.out.println(
            "Configure your game, input the average number of pebble: "
        );
        String inputAvgNumPebbles = this.inputScanner.nextLine();
        avgNumPebbles = Integer.parseInt(inputAvgNumPebbles);
        
        final Vector<Integer> numPebbles =
            this.random(this.numPits, avgNumPebbles * this.numPits);
        
        this.resetBoard(numPebbles);

        System.out.print(
            "Configure your game, input time limit for each move in millisecond: "
        );
        String inputTime = this.inputScanner.nextLine();
        this.time = Integer.parseInt(inputTime);
        
        Boolean running = true;
        while (running) {
            
            // getting input from user
            System.out.print("Please input a command: ");
            
            String inputString = this.inputScanner.nextLine();
            
            String[] inputArgument = inputString.split(" ");
            
            switch (inputArgument[0]) {
            case "help":
                System.out.println(
                    "Commands available are: \n" + "help: show help\n"
                                   + "move {side} {column}: move pebble\n"
                                   + "display: show board status"
                );
                break;
            
            case "display":
                this.displayBoard();
                break;
            
            case "move":
                long t = System.currentTimeMillis();
                long end = t + this.time;
                
                int side = Integer.parseInt(inputArgument[1]);
                int column = Integer.parseInt(inputArgument[2]);

                while (System.currentTimeMillis() < end) {
                    if (this.movePebble(side, column)) {
                        System.out.println("You got another chance!");
                    } else {
                        System.out.println("Warning: your turn ends");
                    }
                    this.displayBoard();
                }
                
            case "exit":
                running = false;
                break;
            
            default:
                System.out.println("Invalid command");
                break;
            }
        }
        
    }
}
