# Game-2332-Repo

02/23/2016:
Name suggestions, pick a name!
Our Choice for title: "Atomic Penguin Warfare"

## *The Idea*
Military pawnguin civil war, scientist just discovered the Atomic Pawnguin, their leaders begin fighting over a fish and thus the war begins on a tile map in a 1v1 turn based game.

## Making The Game
Game is written in C++ and based on Directx9 and FMOD. 
Engine and Windows framework are custom built by Issac Irlas.
Art is by Patricia Sipes.
Menu System by Nicholas Pastrano.
Game Requirements set by class assigment.
Game Design group developed and implemented.

## Mechanics

##### Play mechanics
    The round begins with 20? turns
    Player one will go first then two
    each complete turn (both players move) the counter will decrement one until it reaches zero
##### Unit mechanics
    pawnguin **pawn**
        movements: moves in any direction 3 spaces
        attack: light damage (10 atk)
        health: light health (20hp)
    pawnguin **hulk** 
        movements: moves in any direction 2 spaces
        attack: high damage  (40atk)
        health: light health (40hp)
    pawnguin **bazookas** 
        movements: move in any direction 1 space
        attack: medium damage  (30 atk)
        health: medium health (60hp)
    pawnguin **the puck** 
        movements: slides across the map up to 5 spaces
        attack: medium damage (20 atk)
        health: light health (30hp)
    pawnguin **the general** 
        movements: moves in any direction 1 space
        attack: light damage (10 atk)
        health: high health (80hp)
##### Win conditions & Lose conditions
    One side loses all their units
    animation plays of the winner sides pawnguin getting the fish
##### Draw conditions
    both sides have pawnguins remaining and run out of turns
##### Environment
    map size 16x16
    Tile Types:
    snow:  normal movement values
    ice:   normal movement value
    Rock:  cannot move past this tile
    Water: cannot move past this tile
##### Classes
**Penguin**
    Game pieces and their attributes are held here
**Player**
    Controls game pieces and contains player information

**Game**
    Driver, contains players.

**TiledBackground**
    Contains the visualisation of the tiles

**TileDescParser**
    Creates tiles via an external config file
