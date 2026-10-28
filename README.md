# Survive 10 Nights in the Forest


## Survive 10 Nights in the Forest este un joc text-based, inspirat din unul din cele mai populare jocuri pe platforma Roblox, "99 Nights in the Forest". 

### Scopul principal al jocului "Survive 10 Nights in the Forest" este de a-ți proteja baza, adică de a menține focul de tabără în viață. Pe parcursul fiecărei zile, numărul de puncte necesar pentru a upgrada focul de tabără se mărește, și rata de scădere crește. În cazul în care focul moare, și nivelul de lumină din bază ajunge la 0 la sfârșitul zilei, jocul se termină imediat, deoarece un cerb mutant va ataca jucătorul, ajungând instant în Game Over.

Pentru a ajunge la ziua 10, jucătorul trebuie:
- să mențină focul de tabără activ cu ajutorul materialelor (lemn, cărbune, canistră de benzină) prin acțiunea de căutare (scavage: jucătorul primește un număr random de resurse, ce rămân în inventar de pe o zi pe alta);
- să adune materialele necesare -- lemn, blană de lup -- pentru a-și upgrada uneltele -- topor, pușcă -- pentru a supraviețui unui *event; jucătorul poate ataca lupi în timp ce dă scavage în pădure, iar entitatea poate dropa între 0-3 resurse;
- un *event care poate duce la game over este atacul cultiștilor din zilele 2,4,6,8 și 10;
- în funcție de nivelul uneltelor putem avea două rezultate: - în cazul în care jucătorul câștigă, nivelul focului crește cu 20% (nivel_foc + [20% * nivel_foc])
                                                             - în cazul în care jucătorul pierde, nivelul focului scade cu 50% (nivel_foc - [50% * nivel_foc] + 1);
- ziua 2 de atac necesită unelte de nivel 1, zilele 4,6 și 8 necesită unelte de cel puțin nivelul 2, iar ziua 10 necesită unelte de nivel 3;
- în zilele 3, 6 și 9, un NPC vizitează baza jucătorului. Comerciantul de piei (Pelt Trader) poate upgrada uneltele jucătorului în funcție de un număr fix de lemn și blană de lup. Fiind în zilele 3, 6 și 9, jucătorul are șanse să învingă grupurile de cultiști care vin în baza lui;
- încă un inamic pe care jucătorul il poate întâlni este cerbul mutant: dacă jucătorul se află în afara zonei sigure (bazei) noaptea, cerbul îl atacă. În schimb, dacă nivelul focului de tabără atinge 0, cerbul poate ataca jucătorul în orice moment al zilei, rezultând în GAME OVER.

Dacă jucătorul reușește să treacă peste ultimul atac al cultiștilor din ziua 10, acesta va primi un premiu, un item pe nume "Medalionul Supraviețuitorului" și un mesaj de victorie.

BASE GAME: [99 Nights in the Forest 🔦](https://www.roblox.com/games/79546208627805/99-Nights-in-the-Forest)
