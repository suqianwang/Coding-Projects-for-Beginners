/**
 * 
 */
package com.kalah46.logic;

/**
 * @author SuqianWang
 *
 */
public class GameState {
    public int player;
    public Farm[] board;

    public GameState() {}
    public GameState(Farm[] board, playerSide side) {
    	this.player = side.toInt();
    	this.board = new Farm[2];
    	this.board = board;
    }
}