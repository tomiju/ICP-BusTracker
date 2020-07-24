# ICP - Projekt 2020

"Bus tracker - Aplikace pro zobrazeni linek hromadne dopravy a sledovani jejich pohybu"
--------

### Autori:
* Tomas Julina (xjulin08)
* Tomas Kantor (xkant14)
		
### Poznamky:
* Prelozitelne na Merlin
* Prelozitelne na Windows 10 (testovana i funkcionalita)
* Prelozitelne na Ubuntu 18.04 (testovana i funkcionalita)
	
### Popis:
1) Po spusteni
* Uzivateli se zobrazi okno pro vyber souboru s mapovym podkladem a jizdnimi rady.
* Priklad mapy je umisten ve slozce examples.

2) GUI
* Cas je zobrazovan v levem hornim rohu aplikace.
* Pod nim se nachazi tlacitko "Set Time" a widget pro nastaveni casu.
* Dale pak tlacitko "Stop/Play" pro zastaveni nebo spusteni simulace.
* Tlacitko "Reset" nastavi cas na hodnotu 0.
* Tlacitko "Speed" nastavi rychlost simulace o rychlosti 1:1 az 1:1000.
* Tlacitko "Zoom In" priblizi pohled.
* Tlacitko "Zoom Out" oddali pohled.

3) Mapa
* Po kliknuti na vozidlo se vozidlo zvyrazni a na mape se zobrazi jeho trasa.
* V GUI se zobrazi podrobne informace o vozidle.

* Po kliknuti na ulici se ulice na mape zvyrazni.
* V GUI se zobrazi podrobne informace o ulici.
* V GUI se zobrazi tlacitko pro nastaveni hustoty provozu "Set Congestion Degree" a vstup pro zadani hodnoty.
* Hodnota udava kolikrat je cesta danou ulici pomalejsi.
* Hodnota je realne cislo vetsi rovno 1. 
* Hodnota 1 znamena normalni rychlost. Hodnota 2 znamena polovicni rychlost atd.
* V GUI se zobrazi tlacitko"Close Street", ktere umozni uzavreni ulice.
* Pokud ulici neprochazi zadna linka simulace pokracuje.
* Pokud je jedna nebo vice linek zasazenych uzavrenim ulice, spusti se editacni mod.
* V tomto modu je uzivatel pozadan o definovani nove trasy pro danou linku.
* Po kliknuti na ulici je tato ulice pridana do trasy dane linky.
* Po kliknuti na tlacitko "Clear New Route" muze uzivatel smazat naklikanou trasu a znova ji definovat.
* Pokud je trasa hotova, uzivatel ji musi potvrdit pomoci tlacitka "Set New Route".
* Toto probehne pro vsechny linky.
* Pokud jsou vsechny zasazene linky definovane program automaticky ukonci editacni mod a simulace pokracuje. 
			
