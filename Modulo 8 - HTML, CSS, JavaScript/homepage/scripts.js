function listen(){

    // Faz o conteudo ocupar todo o espaço vertical
    let body = document.getElementsByTagName('body')[0];
    let content = document.getElementsByTagName('main')[0];
    if(content.clientHeight < window.innerHeight){
        body.style.height = '100%';
        content.style.height = '100%';
        document.querySelector('footer').classList.add('fixed-bottom');
    }
}
document.addEventListener('DOMContentLoaded', listen);