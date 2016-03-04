# Game-2332-Repo

02/23/2016:
Name suggestions, pick a name!
Our Choice for title: "Atomic Pawnguin Smackdown"

## *The Idea*
Military pawnguin civil war, scientist just discovered the Atomic Pawnguin, their leaders begin fighting over a fish and thus the war begins on a tile map in a 1v1 turn based game.

## Making The Game
We are using a custom engine created in another class by 2 of our memebers.

## Mechanics

##### Play mechanics
    The round begins with 20? turns
    Player one will go first then two
    each complete turn (both players move) the counter will decrement one until it reaches zero
##### Unit mechanics
    pawnguin **pawn**
        movements: moves in any direction 3 spaces
        attack: light damage
        health: light health (2hp)
    pawnguin **hulk** 
        movements: moves in any direction double (6) spaces
        attack: light damage
        health: light health (1p)
    pawnguin **bazookas** 
        movements: move in any direction 1 space
        attack: medium damage
        health: medium health (4hp)
    pawnguin **the puck** 
        movements: slides across the map up to 5 spaces
        attack: medium damage
        health: light health (2hp)
    pawnguin **the general** 
        movements: moves in any direction 1 space
        attack: light damage
        health: high health (5hp)
##### Win conditions & Lose conditions
    One side loses all their units
    animation plays of the winner sides pawnguin getting the fish
##### Draw conditions
    both sides have pawnguins remaining and run out of turns
##### Environment
    map size 16x16 or 32x32
    Tile Types:
    snow: normal movement values
    ice: increase movement value
    Rock: cannot move past this tile
    Water: reduces movement value
##### Classes
**Unit**

**Player**

**Game**

**Map**

**TILETYPE**
