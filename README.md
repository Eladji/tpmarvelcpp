Collecting workspace information# Marvel Superhero Game

A C++ turn-based game featuring Marvel superheroes battling it out with special abilities and items.

## Project Overview

This game allows players to build teams of superheroes from the Marvel universe and battle against each other. Each hero has unique abilities, attacks, and special moves. Players can also use artifacts to enhance their heroes or hinder opponents.

## Features

- Turn-based combat system
- Multiple playable superheroes: Spider-Man, Hulk, Iron Man, and Doctor Strange
- Unique special abilities for each character
- Item/artifact system including:
  - Health Potions
  - Power Amulets
  - Cursed Stones
- Critical hit system
- Energy-based special attack mechanics

## Installation

### Prerequisites
- C++11 compatible compiler (g++ recommended)
- Make

### Building the Game
```bash
# Clone the repository
git clone https://github.com/yourusername/marvelgame.git
cd marvelgame

# Build the game
make

# Run the game
make run
# or
./marvelgame
```

## How to Play

1. Start the game and enter the number of players
2. Each player chooses a name
3. Build your team by selecting 4 heroes:
   - Hulk: High health, rage mechanics
   - Spider-Man: Balanced stats, web abilities
   - Iron Man: Technology-based attacks
   - Doctor Strange: Magic attacks with AOE capabilities
4. Choose 3 artifacts to add to your inventory
5. During your turn, you can:
   - Attack an opponent
   - Use an artifact
   - Switch heroes

## Class Structure

- `SuperHero`: Base class for all heroes
  - Subclasses: `SpiderMan`, `Hulk`, `IronMan`, `DocteurStrange`
- `Artefacts`: Base class for all items
  - Subclasses: `HealthPotion`, `PowerAmulet`, `CursedStone`
- `Player`: Manages hero teams and inventories
- `Game`: Controls game flow and turn management

## Development

This project demonstrates object-oriented programming concepts in C++:
- Inheritance and polymorphism
- Pure virtual functions
- Memory management
- STL collections

## Authors

- ELadji
- Contributors Myself

## License

This project is licensed under the MIT License - see the LICENSE file for details.