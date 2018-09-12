package com.kalah46.types;

import java.util.Vector;

abstract public class SeedContainer {

    Vector<Integer> container;

    protected SeedContainer() {
        this.container = new Vector<>();
    }

    protected SeedContainer(int size) {
        this.container = new Vector<>(size);
    }

    public void addAllPebbles(Vector<Integer> pebbles) {
        this.container.addAll(pebbles);
    }

    public void addPebble() {
        this.container.add(1);
    }

    public Vector<Integer> clearPebble() {
        Vector<Integer> temp = new Vector<>(this.container);
        this.container.clear();
        return temp;
    }

    public int countPebble() {
        return this.container.size();
    }
}
