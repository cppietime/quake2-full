# Quake 2 Farming Mod
# NJIT Spring 2021
# IT 266 Final Project by Yaakov Schectman

## Currency
There is now a currency stat associated with the player that is displayed on the HUD.  

## Planting seeds
The 0 key has been remapped to a plant function. Keys 1 through 5 select weapons, as usual, which each correspond to a different crop to plant upon the plant action being performed. Each seed type has an associated cost that must be paid when its crop is planted. If you haven't enough money, planting will fail.  

1: Blaster - Soldier: $10  
2: Railgun - Brain: $20  
3: Chaingun - Chick: $50  
4: Shotgun - Berserker: $200  
5: BFG10K - Gladiator: $1000  

## Harvest
Each plant has a cooldown timer that counts down, starting from when it is planted. When the timer counts down, it resets to a crop-specific default starting value and rewards the player with its crop's value in currency. This happens automatically.  

## Watering
When firing at one of your crops with the Blaster equipped, you will attempt to water that crop. Much like the harvest timer, each crop has a watering timer that counts down to the next time it can be watered. A successful watering more quickly decreases the wait time until the crop will next be harvested.  

## Fertilizing
When attacking a crop with the Railgun, you will attempt to fertilize it. Fertilizing also has a countdown timer. Each successful fertilization slightly increases that crop's value for future harvests.  

## Pruning
When using the Chaingun on a crop, you will attempt to prune it. Pruning a crop brings it closer to death, but also rewards you with a little bit of currency in exchange, like a sort of sell-back.  

## Shop
As mentioned above, each seed type has an associated cost that must be paid each time you try to plant one. In addition, the Railgun and Chaingun, the items needed for fertilizing and pruning, come at a cost. The first time you attempt to equip either, if you have enough money, you will automatically pay it and receive the weapon in exchange. The Shotgun and BFG10K are free, as they have no function except to plant specific crops.  

2: Railgun - Fertilizing: $60
3: Chaingun - Pruning: $100

## Upgraded Items
The 9 key has been remapped to swapping the item mode of the player between default and upgraded. In order to buy upgraded items, you must spend $100 the first time. After that, while upgraded items are equipped, watering, fertilizing, and pruning all have extra strength. Pruning, in fact, will 1-shot any crop and immediately kill it.  

## Installing
Unzip the farmingmod.zip file into your quake2 directory and run the included .bat file.