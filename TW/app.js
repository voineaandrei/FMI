const express = require('express');/*include modulul express
memorand in variabila express obiectul asociat modulului(exportat de modul)*/
var app = express();
//const bodyParser = require('body-parser');
const session = require('express-session')
const formidable = require('formidable');
const fs = require('fs');
const util = require('util');
const nodemailer = require("nodemailer");

const crypto = require('crypto');

// initializari socket.io
const http=require('http')
const socket = require('socket.io');
const server = new http.createServer(app);  
var  io= socket(server)
io = io.listen(server);//asculta pe acelasi port ca si serverul


var conexiune_index
io.on("connection", (socket) => {  
    console.log("Conectare!");
	conexiune_index=socket
    socket.on('disconnect', () => {conexiune_index=null;console.log('Deconectare')});
});


function getJson(numeFis){
	let textFis = fs.readFileSync(numeFis);//pun continutul fisierului useri.json in rawdata
	return JSON.parse(textFis);//obtin obiectul asociat json-ului
}

function saveJson(obJson, numeFis){
	let data = JSON.stringify(obJson);//transform in JSON
	fs.writeFileSync(numeFis, data);//scriu JSON-ul in fisier (inlocuind datele vechi)
}

serverPass="tralala";

// pentru folosirea ejs-ului 
app.set('view engine', 'ejs');

//app.use(bodyParser.urlencoded({ extended: false }));
//app.use(bodyParser.json());
app.use(express.static(__dirname));

//setez folderele statice (cele in care nu am fisiere generate prin node)
app.use('/css', express.static('css'));
app.use('/uploads', express.static('uploads'));


//setez o sesiune
app.use(session({
  secret: 'abcdefg',//folosit de express session pentru criptarea id-ului de sesiune
  resave: true,
  saveUninitialized: false
}));

app.get('/', function(req, res) {

	/*afiseaza(render) pagina folosind ejs (deoarece este setat ca view engine) */
    res.render('html/index', {user: req.session.username});

});

app.get('/contact', function(req, res) {
	
	res.render('html/contact', {user: req.session.username});
	
});

app.get('/meniu', function(req, res) {
	
	res.render('html/meniu', {user: req.session.username});
	
});

app.get('/tarif', function(req, res) {
	
	res.render('html/tarif', {user: req.session.username});
	
});
	
app.get('/joc', function(req, res) {
	
	res.render('html/joc', {user: req.session.username});
	
});

// LOGIN

app.post('/joc', (req, res) => {
	var form = new formidable.IncomingForm();
	form.parse(req, function(err, fields, files) {
		
		jsfis=getJson('useri.json');
		
		// parola
		var cifru = crypto.createCipher('aes-128-cbc', 'mypassword');
		var encrParola= cifru.update(fields.parola, 'utf8', 'hex');
		encrParola+=cifru.final('hex');
		
		// caut userul in "useri" 
		let user=jsfis.useri.find(function(x){
			
			return (x.username == fields.username && x.parola == encrParola);
			
		});
		
		if(user){
			console.log(user);
			console.log(user.parola);
			console.log(encrParola);
			req.session.username=user;
			res.render('html/joc',{user: req.session.username});
		}
		else 
		res.render('html/joc',{user: req.session.username});
		
	});
});


app.get('/logout', function(req, res) {
	
	res.render('html/logout', {user: req.session.username});
	
});

app.post('/logout', (req, res) => {
	
	req.session.destroy();
	res.render('html/logout');
	
}); 

app.get('/signup', function(req, res) {
	
	res.render('html/signup', {user: req.session.username});
	
});
	
// INREGISTRARE
	
app.post('/signup', (req, res) => {
	
	var form = new formidable.IncomingForm();
	
	form.parse(req, function(err, fields, files) {

		let rawdata = fs.readFileSync('useri.json');
		let jsfis = JSON.parse(rawdata);
		
		var cifru = crypto.createCipher('aes-128-cbc', 'mypassword');
		var encrParola= cifru.update(fields.parola, 'utf8', 'hex');
		encrParola+=cifru.final('hex');
		
		console.log(fields.parola+ " " +encrParola);
		
		jsfis.useri.push({id:jsfis.lastId, username:fields.username, nume:fields.nume, parola: encrParola, dataInreg: new Date()});
		jsfis.lastId++;	
		res.render('html/signup', {user: req.session.username, rsstatus:"ok"});
		
		saveJson(jsfis,'useri.json')
    }); 
	
});

app.use(function(req,res){
    res.status(404).render('html/404');
});

server.listen(8080)
console.log('Serverul a pornit pe portul 8080');

