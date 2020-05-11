ICP - Project 2020

"Bus tracker - Aplikace pro zobrazeni linek hromadne dopravy a sledovani jejich pohybu"
Autori:
		Tomas Julina (xjulin08)
		Tomas Kantor (xkant14)
		
Poznamky:
	Prelozitelne na Merlin
	Prelozitelne na Windows 10 (testovana i funkcionalita)
	Prelozitelne na Ubuntu 18.04 (testovana i funkcionalita)
	
Popis:
	1) Po spusteni
		Uzivateli se zobrazi okno pro vyber souboru s mapovym podkladem a jizdnimi rady.
		Priklad mapy je umisten ve slozce examples.

	2) GUI
		Cas je zobrazovan v levem hornim rohu aplikace.
		Pod nim se nachazi tlacitko Set Time a widget pro nastaveni casu.

		Dale pak tlacito Stop/Play pro zastaveni nebo spusteni simulace.

		Tlacitko Reset nastavi cas na hodnotu 0.

		Tlacitko Speed nastavi rychlost simulace o rychlosti 1:1 az 1:1000.

		Tacito Zoom In priblizi pohled.

		Tlacito Zoom Out oddali pohled.

	3) Mapa
		Po kliknuti na vozidlo se vozidlo zvyrazni a na mape se zobrazi jeho trasa.
		V GUI se zobrazi info o vozidle.

		Po kliknuti na ulici se ulice na mape zvyrazni.
		V GUI se zobrazi info o ulici.
		V GUI zobrazi tlacitko pro nastaveni hustotoy provozu Set Congestion Degree a vstup pro zadani hodnoty.
			Hodnota udava kolikrat je cesta danou ulici pomalejsi.
			Hodnota je realne cislo vetsi rovno 1. 
			Hodnota 1 znamena normalni rychlost. Hodnota 2 znamena polovicni rychlost atd.
		V GUI se zobrazi tlacitko Close Street, pro uzavreni ulice.
			Pokud ulici neprochazi zadna linka simulace pokracuje.
			Pokud je jedna nebo vice linek zasazenych spusti se editacni mod.
			V tomto modu je uzivatel pozadan o definovani nove trasy pro danou linku.
			Uzivatel trasu definuje naklikanim ulic v mape.
			Pokud je trasa hotova uzivetl ji nastavi pomoci tlacitka Set Route.
			Toto probehne pro vsechny trasy.
			Pokud jsou vsechny zasazene trasy definovane program ukonci editacni mod. 
			
