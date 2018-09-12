package com.kalah46.types;

public enum playerSide {
  /* @formatter:off */
    front(true),
    back(false);
  /* @formatter:on */

    final boolean isFront;
    
    playerSide(boolean isFront) {
        this.isFront = isFront;
    }

    public boolean isFront() {
        return this.isFront;
    }
    
    public playerSide opposite() {
        return this.isFront ? back : front;
    }
    
    public int oppositeI() {
        return this.opposite().toInt();
    }
    
    public int toInt() {
        return this.isFront ? 0 : 1; // Front player, back player
    }
}
