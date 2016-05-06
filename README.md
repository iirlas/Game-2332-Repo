![alt text] (Atomic Penguin SmackDown/Assets/GUIset/splash.png "Putting the Pawn in Pawnguin.")


## Concept
It's a tale as old as time: Two families fight for--well, no one knows  quite for sure; they say it started with a fish (how did it end up like this?), but now these militaristic penguins have a secret weapon to end their feud: Mutation via atomic waste.

## Game Description
####
    2 player, 1v1, turn-based strategy game

## Team Background
##### 
    Game is written in C++ and based on Directx9 and FMOD. 
    Engine and Windows framework are custom built by Issac Irlas.
    Art is by Patricia Sipes.
    Menu System by Nicholas Pastrano.
    Game Requirements set by class assigment.
    Game Design group developed and implemented.
    
    
## Game Run Requirements
####
    1. Only runs on Windows machines
    2. Directx9 must be installed to run
    3. Working keyboard and mouse/trackpad are required for controls
    4. Game is built for TWO(2) players.

## Gameplay Overview
####
    Board is selected via internal randomization.
    Players take turns moving penguins their alotted spaces and attacking until:
         1. One player has no more units alive.
         2. Neither player has taken damage in 10 rounds.
    The active player will have their name (green or blue) highlighted.
    Attacking is automatically applied to the penguin you are facing at the end of movement.

    
## Controls
####
    For each move, click the desired penguin to move it.
    Move with the **arrow keys**.
    To undo a move, press **backspace**
    To commit your move, press **enter/return**
    
         
## Tile Types
####
![alt text] (Atomic Penguin SmackDown/Assets/Environment/radioactive.png "should it be glowing?")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/water2.png "splish splash")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/rock1.png "Where's Bullwinkle?")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/ground.png "Is this terra firma?")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/ice5.png "Ice to know you're reading hover text")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/snow.png "Snow doubt about it, these puns are awful.")


 
#### ATOMIC WASTE
    **Special Tile**
    Only **PAWNS** can enter the waste.
    The first pawn that enters from each team will automatically be **SACRIFICED**
    The second pawn will then turn into a **HULK**. Health and Damage increasing
#### WATER
    Unpassable.
    Penguins might get their suits wet!
#### ROCK
    Unpassable.
    It's like stepping on legos!
#### GROUND
    No movement effects.
#### ICE
    No movement effects.
#### SNOW
    No movement effects.

    
## Penguins
![alt text] (Atomic Penguin SmackDown/Assets/penguins/01PawnFRONT.png "It's a stick!") 
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02PawnFRONT.png "It's another stick!")
#### PAWN
    **See Radiocative Tile for Sacrifice Information**
    movements: moves in any direction 3 spaces
    attack: light damage (10 atk)
    health: light health (30hp)


![alt text] (Atomic Penguin SmackDown/Assets/penguins/01SliderLEFT.png "Could you imagine hockey with a squawking puck?")
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02SliderRIGHT.png "Squawk Squawk")
#### SLIDER(Puck)
    movements: slides across the map up to 5 spaces
    attack: medium damage (20 atk)
    health: light health (40hp)
    
![alt text] (Atomic Penguin SmackDown/Assets/penguins/01BazookaFRONT.png "Boom Boom")
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02BazookaFRONT.png "Bang Bang")
#### BAZOOKA(Joe)
    movements: move in any direction 1 space
    attack: medium damage  (30 atk)
    health: medium health (60hp)
 
![alt text] (Atomic Penguin SmackDown/Assets/penguins/01GeneralFRONT.png "Here comes the General!")
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02GeneralFRONT.png "I'm a general General.")
#### THE GENERAL
    movements: moves in any direction 1 space
    attack: light damage (10 atk)
    health: high health (80hp)
    
![alt text] (Atomic Penguin SmackDown/Assets/penguins/01HulkFRONT.png "Hulk Smash?")
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02HulkFRONT.png "Hulk Smash.")
#### HULK
    **See Radiocative Tile for Sacrifice Information**
    movements: moves in any direction 2 spaces
    attack: high damage  (40atk)
    health: light health (50hp)




## Programming Structure (Classes)
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
    
**GameUI**
    Holds UI elements/HUD
    
**Collision Manager**
    dictates how objects interact with each other
    
**Game Interface**
    States manager
    
**Game Run**
    States driver
    
**Game Win Conditions**
    Three classes that control end screens for stalemate, blue, or green victory.
    
**Other programming notes**
    Levels are created through parse of a config file, file choice is randomised. An animation file controls all items by looking at their location on the sprite sheets.
