package com.kalah46.types;

import java.util.ArrayList;
import java.util.Vector;

public class Farm {
    
    public ArrayList<House> pits;
    public Store            resourcePool;

    public Farm(int numPits, Vector<Integer> numPebbles) {
        this.resourcePool = new Store();
        this.pits = new ArrayList<>();
        for (int i = 0; i < numPits; i++) {
            this.pits.add(new House(numPebbles.get(i)));
            for (int j = 0; j < numPebbles.get(i); j++) {
                this.pits.get(i).addPebble();
            }
        }
        return;
    }
    
    public boolean checkEmpty(Farm thisPlayer, int numPits) {
        for (int i = 0; i < numPits; i++) {
            if (thisPlayer.pits.get(i).countPebble() != 0) { return false; }
        }
        return true;
    }
}
