![alt text] (Atomic Penguin SmackDown/Assets/GUIset/splash.png "Putting the Pawn in Pawnguin.")


## *Concept*
It's a tale as old as time: Montagues and Capulets, Sharks and Jets, Hatfields and McCoys. Blue and Green Penguin Families. They say it started with a fish (how did it end up like this?), but now these militaristic penguins have a secret weapon to end their fued: Mutation via atomic waste.

## Team Background
##### 
    Game is written in C++ and based on Directx9 and FMOD. 
    Engine and Windows framework are custom built by Issac Irlas.
    Art is by Patricia Sipes.
    Menu System by Nicholas Pastrano.
    Game Requirements set by class assigment.
    Game Design group developed and implemented.

## Mechanics

##### Gameplay Overview
    Board is selected via internal randomization.
    Players take turns moving penguins their alotted spaces and attacking until:
         1. One player has no more units alive.
         2. Neither player has taken damage in 10 rounds.
         
#### Tile Types
![alt text] (Atomic Penguin SmackDown/Assets/Environment/radioactive.png "should it be glowing?")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/water2.png "splish splash")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/rock1.png "Where's Bullwinkle?")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/ground.png "Is this terra firma?")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/ice5.png "Ice to know you're reading hover text")
![alt text] (Atomic Penguin SmackDown/Assets/Environment/snow.png "Snow doubt about it, these puns are awful.")


 
##### Atomic Waste
    **Special Tile**
    Only **PAWNS** can enter the waste.
    The first pawn that enters from each team will automatically be **SACRIFICED**
    The second pawn will then turn into a **HULK**. Health and Damage increasing
##### Water
    Unpassable.
    Penguins might get their suits wet!
##### Rock
    Unpassable.
##### Ground
    No movement effects.
##### Ice
    No movement effects.
##### Snow
    No movement effects.

    
#### Penguins
![alt text] (Atomic Penguin SmackDown/Assets/penguins/01PawnFRONT.png "It's a stick!") 
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02PawnFRONT.png "It's another stick!")
##### PAWN
    **See Radiocative Tile for Sacrifice Information**
    movements: moves in any direction 3 spaces
    attack: light damage (10 atk)
    health: light health (30hp)

![alt text] (Atomic Penguin SmackDown/Assets/penguins/01SliderLEFT.png "Could you imagine hockey with a squawking puck?")
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02SliderRIGHT.png "Squawk Squawk")
##### SLIDER(Puck)
    movements: slides across the map up to 5 spaces
    attack: medium damage (20 atk)
    health: light health (40hp)
    
![alt text] (Atomic Penguin SmackDown/Assets/penguins/01BazookaFRONT.png "Boom Boom")
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02BazookaFRONT.png "Bang Bang")
##### BAZOOKA(Joe)
    movements: move in any direction 1 space
    attack: medium damage  (30 atk)
    health: medium health (60hp)
 
![alt text] (Atomic Penguin SmackDown/Assets/penguins/01GeneralFRONT.png "Here comes the General!")
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02GeneralFRONT.png "I'm a general General.")
##### THE GENERAL
    movements: moves in any direction 1 space
    attack: light damage (10 atk)
    health: high health (80hp)
    
![alt text] (Atomic Penguin SmackDown/Assets/penguins/01HulkFRONT.png "Hulk Smash?")
![alt text] (Atomic Penguin SmackDown/Assets/penguins/02HulkFRONT.png "Hulk Smash.")
##### HULK
    **See Radiocative Tile for Sacrifice Information**
    movements: moves in any direction 2 spaces
    attack: high damage  (40atk)
    health: light health (50hp)




#### Programming Structure (Classes)
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
    
**Other programming notes**
    Levels are created through parse of a config file, file choice is randomised. An animation file controls all items by looking at their location on the sprite sheets.
