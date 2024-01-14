import { Prodavnica } from "./prodavnica.js";

export class Application {
  constructor(prodavnice, kategorije) {
    this.prodavnice = [];
    this.kategorije = kategorije;
    prodavnice.forEach((proiz, prod) => {
      this.prodavnice.push(
        new Prodavnica(prod.id, prod.naziv, kategorije, proiz)
      );
    });
  }

  draw(container) {
    const mainDiv = document.createElement("div");
    mainDiv.classList.add("main-div");
    container.appendChild(mainDiv);

    this.prodavnice.forEach((p) => p.draw(mainDiv));
  }
}
