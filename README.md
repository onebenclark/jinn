# Project Jinn Development Log

## Project Jinn is to be a Party Based RPG in the vein of the Dragon Age games.

### 1-8-20:
>Well it seems I've done a bad job keeping up this dev log up to date. I've established the ground work for developing new actions.
>I switched the to a new animation set I've gotten from the market place, which will not be added to the repo. 

### 9-2-19:
>I've imported the mannequin from one of UE4's sample projects to use with creatures.
>For now I'm using the animation blueprint included with it for now until I get the chance to replace.
>This week I hope to continue to develop the basic attacks.

### 8-26-19:
>After looking into the Gameplay Ability System for several days I have decided not to use it for this project.
>I definitely see the utility for larger scoped projects and projects with online features, but for this small project it won't be necessary.

### 8-22-19: 
>I've decided to use this README as a dev log for this project. I am working towards implementing basic combat between Creatures in the game. 
>I've recently decide to use a PawnSensingComponent to make a basic agro check to initiate a combat state for Creatures, but the Agro check will be expanded and refined.
>This will be used in Behavior Trees so the AI knows when to follow the combat paths of the tree. I need to create a basic attack for the creatures to use when in combat.
>I am hoping to use the Gameplay Abilities features to implement attacks, spells, etc.
