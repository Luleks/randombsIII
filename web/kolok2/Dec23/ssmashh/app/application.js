import { Prodavnica } from "./Prodavnica.js";

export class Application {
  constructor(prodavnice_proizvodi, kategorije) {
    this.prodavnice = [];
    prodavnice_proizvodi.forEach((v, k) => {
      this.prodavnice.push(new Prodavnica(k.id, k.naziv, kategorije, v));
    });
  }

  draw(container) {
    const mainDiv = document.createElement("div");
    mainDiv.classList.add("main-div");
    container.appendChild(mainDiv);

    this.prodavnice.forEach((p) => p.draw(mainDiv));
  }
}
