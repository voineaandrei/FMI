/*
1. La radio.checked => merge in for pt i = 0, dar cand iese automat primeste fals.
*/

/* mancare =["Salata", "Pizza cu ton", "Pizza Margherita", "Pizza Diavola", "Pizza Capriciosa", "Coca Cola", "Pepsi", "Ceafa de porc", "Apa"];
culori = ["red", "blue", "green"];
buget = ["1000", "2000", "3000"];
gameStarted = 0;
clientiPierduti = 0;

isDown = false;
offset = [];
idClient = 0;


mancareDorita = [];
intervaleMese = [];
nrIntervale = 0; */

window.onload=function(){
	var audio = new Audio('/audio/melody.mp3');
	const playedPromise = audio.play();
		if (playedPromise) {
        playedPromise.catch((e) => {
            if (e.name === 'NotAllowedError' ||
                e.name === 'NotSupportedError') {
                //console.log(e.name);
            }
        });
    }
	
	var h1 = document.createElement("h1");
	var txtNode = document.createTextNode("Setarile jocului: ");
	h1.appendChild(txtNode);
	h1.style.fontSize = "30px";
	h1.style.textAlign = "center";
	document.body.appendChild(h1);
	
	/* input_range pt coloane */
	document.body.innerHTML += '<p>Alege cati clienti trebuie sa plece pana sa pierzi</p>';
	input1 = document.createElement("input");
	input1.id = "pierdere";
	input1.type = "range";
	input1.min = 5;
	input1.max = 10;
	input1.setAttribute("value",5);
	document.body.appendChild(input1);
	document.body.innerHTML += "<br/>";
	
	/* input_text pt numele jucatorului */
	document.body.innerHTML += '<p>Numele jucatorului </p>';
	input1 = document.createElement("input");
	input1.type = "text";
	document.body.appendChild(input1);
	document.body.innerHTML += "<br/>";
	
	/* input_checkbox pt fiecare fel de mancare posibil*/
	document.body.innerHTML += '<p>Meniul va fi: </p>';
	for (let i = 0; i < mancare.length; i++) {
		input1 = document.createElement("input");
		input1.type = "checkbox";
		input1.id = mancare[i];
/**/	input1.setAttribute("onchange","schimbCuloare("+i+")"); // DACA PUNEAM INPUT1.ID IMI DA EROAREA _ MISSING ')' AFTER ARGUMENT LIST
		
		let newlabel = document.createElement("label");
		newlabel.setAttribute("for",mancare[i]);
		newlabel.innerHTML = mancare[i];
		
		document.body.appendChild(input1);
		document.body.appendChild(newlabel);
		document.body.innerHTML += '<br/>';
	}
	
	/* input_radio culoarea meselor */
	document.body.innerHTML += '<p>Mesele vor avea culoarea: </p>';
	for (let i = 0; i < culori.length; i++) {
		input1 = document.createElement("input");
		input1.type = "radio";
		input1.name = "culoare";
		input1.value = culori[i];
		input1.id = culori[i];
		if (i == culori.length-1) input1.setAttribute("checked",true);
		
		let newlabel = document.createElement("label");
		newlabel.setAttribute("for",culori[i]);
		newlabel.innerHTML = culori[i];
		
		document.body.appendChild(input1);
		document.body.appendChild(newlabel);
		document.body.innerHTML += "<br/>";
	}
	
	/* select_simplu va seta bugetul initial */
	document.body.innerHTML += '<p>Bugetul: </p>';
	
	input1 = document.createElement("select");
	input1.id = "sele";
	for (let i = 0; i < buget.length; i++) {
		let input2 = document.createElement("option");
		input2.innerHTML = buget[i];
		input2.value = buget[i];
		input1.add(input2);
	}
	document.body.appendChild(input1);
	document.body.innerHTML += "<br/>";
	
	/* textarea feluri suplimentare */
	document.body.innerHTML += '<p>Feluri suplimentare</p>';
	input1 = document.createElement("textarea");
	document.body.appendChild(input1);
	document.body.innerHTML += "<br/>";
	
	/*Buton pentru inceperea jocului*/ //ia datele din inputuri si genereaza jocul
	var btn = document.createElement("button");
	btn.innerHTML = "START";
	btn.id = "btn";
	btn.setAttribute("onclick", "startGame()");
	document.body.appendChild(btn);

};

// APARE GAME AREA

function startGame() {
	if (gameStarted == 0) { // daca e deja ecranul, nu-l mai cream
		gameStarted = 1;
		clientiLaCarePierzi = document.getElementById("pierdere").value;
		
		var gameArea = document.createElement("div");
		gameArea.id = "gameArea";
		document.body.appendChild(gameArea);
		
		// Aflam numele
		nume = document.querySelector('input[type=text]').value;
		var div = document.createElement("div");
		div.style.color = "black";
		div.appendChild(document.createTextNode("Numele jucatorului: "));
/**/	div.innerHTML += '<b><i>'+nume+'</i></b>'; // CUM POT FACE ASTA FARA CONCATENARE??
		if (nume == "")
			div.innerHTML += "Nu are nume";
		div.innerHTML += " ; Buget ramas: ";
		
		// Aflam bugetul
		var bugetCollection = document.querySelectorAll('option');
		for (let i = 0; i < bugetCollection.length; i++) {
			if (bugetCollection[i].selected == true)
				bugetActual = bugetCollection[i].value;
		}
		
		// Bag bugetul intr-un 'paragraph' ca sa pot edita innerHTML-ul mai tarziu, actualizand bugetul
		var p = document.createElement("p");
		p.innerHTML = bugetActual;
		p.style.display = "inline-block";
		p.id = "buget";
		div.appendChild(p);
		
		gameArea.appendChild(div);
		
		var meseStanga = document.createElement("div"); //mesele din stanga
		meseStanga.id = "meseStanga";
		gameArea.appendChild(meseStanga);
		var meseDreapta = document.createElement("div"); //mesele din dreapta
		meseDreapta.id = "meseDreapta";
		gameArea.appendChild(meseDreapta);
		
		// Cum arata mesele
		var tableColor;
		var color = document.getElementsByName("culoare");
		for (i = 0; i < color.length; i++) {
			if (color[i].checked == true)
				tableColor = color[i].value;
		}
	
		// Vedem cate mese sunt pe coloana, ca sa stim cate linii facem cu mese.
		for (let i = 0; i < 6; i++) { 
			var div = document.createElement("div");
			div.id = "masa"+i;
			div.value = i;
			div.style.backgroundColor = tableColor;
			//div.style.backgroundImage = "url('./Images/green_table.png')";
			if (i % 2 == 0) {
				meseStanga.appendChild(div);
			}
			else
				meseDreapta.appendChild(div);
		}
		
		// Luam felurile de mancare available
		// IN VECTORUL mancareActuala avem toate felurile gasite in jocul actual
		var mancareCollection = document.querySelectorAll('input[type=checkbox]');
		mancareActuala = [];
		for (let i = 0; i < mancareCollection.length; i++) {
			if (mancareCollection[i].checked == true)
				mancareActuala.push(mancareCollection[i].id);
		}
		var txt = document.getElementsByTagName("textarea")[0].value;
		if (txt != "") {
			var rez = txt.split(", ");
			for (let i of rez)
				mancareActuala.push(i);
		}
		
		// IN VECTORUL mancareCost, fiecare mancareCost[i] reprezinta costul felului de pe mancareActuala[i]
		
		mancareCost = [];
		for (let i = 0; i < mancareActuala.length; i++){
			switch(Math.floor(Math.random() * Math.floor(3))){
				case 0:
					mancareCost[i] = 100;
					break;
				case 1:
					mancareCost[i] = 150;
					break;
				case 2:
					mancareCost[i] = 200;
			};
		}
		
		// Vector ca sa numar fiecare tip de mancare
		mancareNumar =[];
		
		// Creez butonele pt fiecare mancare
		var div = document.createElement("div");
		div.id = "butoane";
		for (let i = 0; i < mancareActuala.length; i++) {
			var btn = document.createElement("button");
			btn.className = "butoane";
			btn.id = "buton" + i;
			btn.setAttribute("onclick","doFood("+i+")");
			btn.innerHTML = mancareActuala[i];
			div.appendChild(btn);
			
			mancareNumar[i] = 0;
			var p = document.createElement("p");
			p.innerHTML = "Aveti 0 din:";
			p.style.color = "black";
			div.insertBefore(p, btn);
		}
		
		//Creez buton pt generateFood
		var btn = document.createElement("button");
		btn.innerHTML = "Genereaza mancare";
		btn.className = "butoane";
		btn.style.backgroundColor = "black";
		btn.setAttribute("onclick","generateFood(" + mancareActuala.length + ")");
		div.appendChild(btn);
		
		gameArea.appendChild(div);
		
		// crearea div-ului cu clientii
		var div = document.createElement("div");
		div.id = "clienti";
		div.style.position = "absolute";
		div.style.bottom = "100px";
		div.style.display = "flex";
		gameArea.appendChild(div);
		
		for (let i = 0; i < 10; i++){
			var div = document.createElement("div");
			div.style.position = "relative";
			div.style.width = "100px";
			div.id = "divClient"+i;
			document.getElementById("clienti").appendChild(div);
		}
		// clientii
		intervalClienti = setInterval(createClient,1000);
		
	}// nu completa nimic aici
}

function createClient() {
	for (let i = 0; i < 10; i++) 
	if (document.getElementById("divClient"+i).firstChild == null) {
		var client = document.createElement("div");
		client.className = "clienti";
		
		// tot if-ul de jos e pt event-uri, astfel doar primul client are eventuri legate de mouse!
		if (i == 0){
			client.addEventListener('mousedown', function(e) {
				isDown = true;
				offset = [
				client.offsetLeft - e.clientX,
				client.offsetTop - e.clientY
				];
			}, true);

			client.addEventListener('mouseup', function(e) {
				isDown = false;
				leftP = parseInt(client.style.left);
				topP = parseInt(client.style.top);
			
				if (leftP > 25 && leftP < 225){
					if (topP > -600 && topP < -500)
						if (document.getElementById("masa0").firstChild == null){
						document.getElementById("masa0").appendChild(client);
						pozitioneaza_client(client);
						mutare_clienti();
					}
					else alert ("ocupat");
					if (topP > -440 && topP < -340)
						if (document.getElementById("masa2").firstChild == null){
						document.getElementById("masa2").appendChild(client);
						pozitioneaza_client(client);
						mutare_clienti();
					}
					else alert ("ocupat");
					if (topP > -280 && topP < -180)
						if (document.getElementById("masa4").firstChild == null){
						document.getElementById("masa4").appendChild(client);
						pozitioneaza_client(client);
						mutare_clienti();
					}
					else alert ("ocupat");
				} // LINIA DE JOS TRB MODIFICATA IN FUNCTIE DE ECRANUL DE JOC
				else if ( leftP > document.documentElement.clientWidth - 225 && leftP < document.documentElement.clientWidth){
					if (topP > -600 && topP < -500)
						if (document.getElementById("masa1").firstChild == null){
						document.getElementById("masa1").appendChild(client);
						pozitioneaza_client(client);
						mutare_clienti();
					}
					else alert ("ocupat");
					if (topP > -440 && topP < -340)
						if (document.getElementById("masa3").firstChild == null){
						document.getElementById("masa3").appendChild(client);
						pozitioneaza_client(client);
						mutare_clienti();
					}
					else alert ("ocupat");
					if (topP > -280 && topP < -180)
						if (document.getElementById("masa5").firstChild == null){
						document.getElementById("masa5").appendChild(client);
						pozitioneaza_client(client);
						mutare_clienti();
					}
					else alert ("ocupat");
				}
			}, true);

			client.addEventListener('mousemove', function(event) {
				event.preventDefault();
				if (isDown) {
					mousePosition = {
						x : event.clientX,
						y : event.clientY
					};
					client.style.left = (mousePosition.x + offset[0]) + 'px';
					client.style.top  = (mousePosition.y + offset[1]) + 'px';
				}
			}, true);
		}
		document.querySelector("#divClient"+i).appendChild(client);
		
		client.id = "client" + idClient;
		idClient++;
		
		break;
	}
}	

// pune clientul in div ul mesei si "primeste" si comanda

function pozitioneaza_client(unDiv){
	unDiv.style.position = "relative";
	unDiv.style.top = "0px";
	unDiv.style.left = "0px";
	
	var masa = unDiv.parentNode;
	
	var comanda = Math.floor(Math.random() * Math.floor(mancareActuala.length));
	mancareDorita[masa.value] = mancareActuala[comanda];
	
	var p = document.createElement("p");
	p.innerHTML = mancareActuala[comanda];
	p.style.color = "black";
	p.style.position = "absolute";
	
	masa.appendChild(p);
	intervaleMese[nrIntervale] = setTimeout(function () { dispare_client(masa) }, 3000);
	p.value = nrIntervale;
	nrIntervale++;
	
}

// mutam toti clientii in dreapta

function mutare_clienti(){
	for (let i = 1; i < 10; i++)
		if (document.getElementById("divClient" + i).firstChild != null) {
			var ind = i - 1;
			var cL = document.getElementById("divClient" + i).firstChild;
			var loc = document.getElementById("divClient" + ind);
			loc.appendChild(cL);
			if (ind == 0) {
				client = document.getElementById("divClient0").firstChild;
				client.addEventListener('mousedown', function(e) {
					isDown = true;
					offset = [
					client.offsetLeft - e.clientX,
					client.offsetTop - e.clientY
					];
					
				}, true);

				client.addEventListener('mouseup', function(e) {
					isDown = false;
					leftP = parseInt(client.style.left);
					topP = parseInt(client.style.top);
			
					if (leftP > 25 && leftP < 225){
						if (topP > -600 && topP < -500)
							if (document.getElementById("masa0").firstChild == null){
							document.getElementById("masa0").appendChild(client);
							pozitioneaza_client(client);
							mutare_clienti();
						}
							else alert ("ocupat");
						if (topP > -440 && topP < -340)
							if (document.getElementById("masa2").firstChild == null){
							document.getElementById("masa2").appendChild(client);
							pozitioneaza_client(client);
							mutare_clienti();
						}
							else alert ("ocupat");
						if (topP > -280 && topP < -180)
							if (document.getElementById("masa4").firstChild == null){
							document.getElementById("masa4").appendChild(client);
							pozitioneaza_client(client);
							mutare_clienti();
						}
							else alert ("ocupat");
					} // LINIA DE JOS TRB MODIFICATA IN FUNCTIE DE ECRANUL DE JOC
					else if ( leftP > document.documentElement.clientWidth - 225 && leftP < document.documentElement.clientWidth){
						if (topP > -600 && topP < -500)
							if (document.getElementById("masa1").firstChild == null){
							document.getElementById("masa1").appendChild(client);
							pozitioneaza_client(client);
							mutare_clienti();
						}
							else alert ("ocupat");
						if (topP > -440 && topP < -340)
							if (document.getElementById("masa3").firstChild == null){
							document.getElementById("masa3").appendChild(client);
							pozitioneaza_client(client);
							mutare_clienti();
						}
							else alert ("ocupat");
						if (topP > -280 && topP < -180)
							if (document.getElementById("masa5").firstChild == null){
							document.getElementById("masa5").appendChild(client);
							pozitioneaza_client(client);
							mutare_clienti();
						}
							else alert ("ocupat");
					}
				}, true);

				client.addEventListener('mousemove', function(event) {
					event.preventDefault();
						if (isDown) {
							mousePosition = {
								x : event.clientX,
								y : event.clientY
							};
							client.style.left = (mousePosition.x + offset[0]) + 'px';
							client.style.top  = (mousePosition.y + offset[1]) + 'px';
						}
				}, true);
			}
				
		}
}

// la "r" se reseteaza
document.onkeydown = function(e){
	if (e.keyCode == 82 && gameStarted == 1) {
		gameStarted = 0;
		document.getElementById("gameArea").remove();
		clearInterval(intervalClienti);
		for (let i = 0; i < intervaleMese.length; i++)
			clearTimeout(intervaleMese[i]);
	}
}
	
function schimbCuloare(nrCurent) {
	var x = document.querySelectorAll('input[type=checkbox]')[nrCurent];
	if (x.checked == true) {
		x.nextSibling.style.color = "#c70039";
	}
	else {
		x.nextSibling.style.color = "#ffc30f";
	}
}

// mancareDorita - mancareDorita[i] retine ce vrea cel de la masa i;

function doFood(nrCurent) {
	if (mancareNumar[nrCurent] != 0) {
		
		for (let i = 0; i < 6; i++){
			if (document.getElementById("masa"+i).firstChild != null && document.getElementById("masa"+i).firstChild.nextSibling.innerHTML == document.getElementById("buton"+nrCurent).innerHTML)
			{
				mancareNumar[nrCurent]--;
				bugetActual += mancareCost[nrCurent] + 50;
				var pbuget = document.getElementById("buget");
				pbuget.innerHTML = bugetActual;
				
				var itv = document.getElementById("masa"+i).firstChild.nextSibling.value;
				clearTimeout(intervaleMese[itv]);
				
				clientiPierduti--;
				var masa = document.getElementById("masa"+i);
				dispare_client(masa);
				
				var p = document.getElementById("buton"+nrCurent).previousSibling;
				p.innerHTML = "Aveti " + mancareNumar[nrCurent] + " din:";
	
				if (mancareNumar[nrCurent] == 0)
				document.getElementById("buton"+nrCurent).style.backgroundColor = "#c70039";
		
				break;
			} 
		}
	}else {
		alert("Nu ai " + mancareActuala[nrCurent]);
		}
}

function generateFood(nrCurent) {
	i = (Math.floor(Math.random() * Math.floor(nrCurent)));
	if (mancareCost[i] <= bugetActual){
		mancareNumar[i]++;
		bugetActual -= mancareCost[i];
		
		var pbuget = document.getElementById("buget");
		pbuget.innerHTML = bugetActual;
	
		var p = document.getElementById("buton"+i).previousSibling;
		p.innerHTML = "Aveti " + mancareNumar[i] + " din:";
	
		document.getElementById("buton"+i).style.backgroundColor = "black"; // evidentiez
	}
}

function schimbaMese(cul) {
	var MESE = document.getElementsByClassName("meseStanga");
	for (let i of MESE)
		i.style.backgroundImage = 'url("./Images/"'+cul+'"_table.png")';
	MESE = document.getElementsByClassName("meseDreapta");
	for (let i of MESE)
		i.style.backgroundImage = 'url("./Images/"'+cul+'"_table.png")';
}


function dispare_client(obj) {
	obj.firstChild.remove();
	obj.firstChild.remove();
	
	clientiPierduti++;
	if (clientiPierduti == clientiLaCarePierzi)
		{
			alert ("Ai pierdut jocul");
			document.getElementById("gameArea").remove();
			gameStarted = 0;
			clearInterval(intervalClienti);
			clientiPierduti = 0;
		}
}

// npm install formidable --save
// npm install express-session --save
// app use
// logout
// var form + formidale
// header.ejs