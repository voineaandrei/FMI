v = ["masa", "casa", "rasa"]

window.onload=function(){
	for (el of v)
		body.appendChild(createTextNode(el));
}