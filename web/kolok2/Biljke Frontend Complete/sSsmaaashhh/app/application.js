import { Biljka } from "./biljka.js";

export class Application {
  constructor(podrucja, osobine) {
    this.podrucja = podrucja;
    this.osobine = osobine;

    this.resultContainer = null;
  }

  draw(container) {
    const naslov = document.createElement("h1");
    naslov.innerHTML = "Lekovito bilje";
    container.appendChild(naslov);

    const mainDiv = document.createElement("div");
    mainDiv.classList.add("main-div");
    container.appendChild(mainDiv);

    const pretragaDiv = document.createElement("div");
    pretragaDiv.classList.add("pretraga-div");
    mainDiv.appendChild(pretragaDiv);
    this.drawPretraga(pretragaDiv);

    this.resultContainer = document.createElement("div");
    this.resultContainer.classList.add("result-div");
    mainDiv.appendChild(this.resultContainer);
  }

  drawPretraga(container) {
    this.drawPodrucja(container);
    this.drawOsobine(container);

    const btnPretrazi = document.createElement("input");
    btnPretrazi.type = "button";
    btnPretrazi.value = "Pretrazi";
    btnPretrazi.onclick = this.onClickPretrazi;
    btnPretrazi.classList.add("margin-10", "btn-pretrazi");
    container.appendChild(btnPretrazi);
  }

  onClickPretrazi = async () => {
    // https://localhost:7011/Biljke/PreuzmiBiljke/1?osobineIDs=1&osobineIDs=2&osobineIDs=3
    const podrucjeDD = document.querySelector(".podrucja-dd");
    const podrucjeID = podrucjeDD.value;
    let baseUrl = `https://localhost:7011/Biljke/PreuzmiBiljke/${podrucjeID}`;
    let query = "?";
    let first = true;
    const unikati = new Set(this.osobine.map((o) => o.naziv));
    unikati.forEach((o) => {
      let dd = document.querySelector(`.dd-${o}`);
      if (first) {
        first = false;
        query += `osobineIDs=${dd.value}`;
      } else {
        query += `&osobineIDs=${dd.value}`;
      }
    });

    const result = await fetch(baseUrl + query)
      .then((response) => response.json())
      .catch((err) => console.error(err));

    this.resultContainer.replaceChildren();

    result.forEach((r) => {
      let biljka = new Biljka(r.id, r.naziv, r.slika, r.brojVidjenja);
      biljka.draw(this.resultContainer);
    });
  };

  drawPodrucja(container) {
    const lbl = document.createElement("label");
    lbl.innerHTML = "Podrucje:";
    lbl.classList.add("margin-10");
    container.appendChild(lbl);

    const dropdown = document.createElement("select");
    dropdown.classList.add("podrucja-dd", "margin-10");
    this.podrucja.forEach((p) => {
      let option = document.createElement("option");
      option.value = p.identifikator;
      option.innerHTML = p.naziv;
      dropdown.appendChild(option);
    });
    container.appendChild(dropdown);
  }

  drawOsobine(container) {
    this.osobine.forEach((o) => {
      let lbl = document.querySelector(`.lbl-${o.naziv}`);
      if (lbl == null) {
        lbl = document.createElement("label");
        lbl.classList.add(`lbl-${o.naziv}`, "margin-10");
        lbl.innerHTML = o.naziv;
        container.appendChild(lbl);
      }
      let dd = document.querySelector(`.dd-${o.naziv}`, "margin-10");
      if (dd == null) {
        dd = document.createElement("select");
        dd.classList.add(`dd-${o.naziv}`, "margin-10");
        container.appendChild(dd);
      }
      let option = document.createElement("option");
      option.value = o.id;
      option.innerHTML = o.vrednost;
      dd.appendChild(option);
    });
  }
}
