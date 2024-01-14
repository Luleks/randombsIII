import { Biljka } from "./biljka.js";

export class Application {
  constructor(podrucja, osobine) {
    this.podrucja = podrucja;
    this.osobine = osobine;

    this.rezultati = null;
  }

  draw(container) {
    const naslov = document.createElement("h1");
    naslov.innerHTML = "Lekovito bilje";
    container.appendChild(naslov);

    const sadrzaj = document.createElement("div");
    sadrzaj.classList.add("sadrzaj");
    container.appendChild(sadrzaj);
    this.drawSearch(sadrzaj);

    this.rezultati = document.createElement("div");
    this.rezultati.classList.add("rezultati");
    sadrzaj.appendChild(this.rezultati);
  }

  drawSearch(container) {
    const searchDiv = document.createElement("div");
    searchDiv.classList.add("search");
    container.appendChild(searchDiv);

    this.drawPodrucje(searchDiv);
    this.drawOsobine(searchDiv);

    const btnPretrazi = document.createElement("input");
    btnPretrazi.type = "button";
    btnPretrazi.value = "Pretrazi";
    btnPretrazi.classList.add("margin-10", "btnPretrazi");
    btnPretrazi.onclick = this.onClickPretrazi;
    searchDiv.appendChild(btnPretrazi);
  }

  onClickPretrazi = async () => {
    const podrucjeDD = document.querySelector(".podrucje-dd");
    const podrucjeID = podrucjeDD.value;

    let url = `https://localhost:7011/Biljke/PreuzmiBiljke/${podrucjeID}`;
    let query = "?";

    let first = true;

    const unikati = new Set(this.osobine.map((o) => o.naziv));
    unikati.forEach((o) => {
      let osobinaID = document.querySelector(`.dd-${o}`).value;
      if (first) {
        query += `osobineIDs=${osobinaID}`;
        first = false;
      } else {
        query += `&osobineIDs=${osobinaID}`;
      }
    });

    const result = await fetch(url + query)
      .then((response) => response.json())
      .catch((err) => console.error(err));

    this.rezultati.replaceChildren();

    result.forEach((r) => {
      let b = new Biljka(r.id, r.naziv, r.slika, r.brojVidjenja);
      b.draw(this.rezultati);
    });
  };

  drawPodrucje(container) {
    const lbl = document.createElement("label");
    lbl.innerHTML = "Podrucje";
    lbl.classList.add("margin-10");
    container.appendChild(lbl);

    const dd = document.createElement("select");
    this.podrucja.forEach((p) => {
      let option = document.createElement("option");
      option.value = p.identifikator;
      option.innerHTML = p.naziv;
      dd.appendChild(option);
    });
    dd.classList.add("podrucje-dd", "margin-10");
    container.appendChild(dd);
  }

  drawOsobine(container) {
    this.osobine.forEach((o) => {
      let lbl = document.querySelector(`lbl-${o.naziv}`);
      if (lbl == null) {
        lbl = document.createElement("label");
        lbl.innerHTML = o.naziv;
        lbl.classList.add(`lbl-${o.naziv}`, "margin-10");
        container.appendChild(lbl);
      }
      let dd = document.querySelector(`dd-${o.naziv}`);
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
