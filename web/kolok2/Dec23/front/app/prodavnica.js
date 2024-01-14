export class Prodavnica {
  constructor(id, naziv, kategorije, proizvodi) {
    this.id = id;
    this.naziv = naziv;
    this.kategorije = kategorije;
    this.proizvodi = proizvodi;

    this.upis_polja = [
      { lbl: "Naziv:", klasa: "naziv", inputType: "text", element: "input" },
      { lbl: "Kat:", klasa: "kategorija", element: "select" },
      { lbl: "Cena:", klasa: "cena", inputType: "number", element: "input" },
      {
        lbl: "Kolicina:",
        klasa: "kolicina",
        inputType: "number",
        element: "input",
      },
    ];
  }
  draw(container) {
    this.drawFrom(container);
    this.drawProdavnica(container);
  }

  drawFrom(container) {
    const formDiv = document.createElement("div");
    formDiv.classList.add("form-div");
    container.appendChild(formDiv);

    const p = document.createElement("p");
    p.classList.add("title");
    p.innerHTML = "Upis proizvoda";
    formDiv.appendChild(p);

    this.drawPolja(formDiv);

    const submit = document.createElement("input");
    submit.type = "submit";
    submit.value = "Dodaj proizvod";
    submit.classList.add(`submit-${this.id}`, "margin-10", "submit-form");
    formDiv.appendChild(submit);
  }

  drawPolja(container) {
    this.upis_polja.forEach((p) => {
      let lbl = document.createElement("label");
      lbl.innerHTML = p.lbl;
      lbl.classList.add("margin-10");
      container.appendChild(lbl);

      let input = document.createElement(p.element);
      if (p.inputType != undefined && p.inputType != null) {
        input.type = p.inputType;
        input.classList.add(`${input.type}-${this.id}`, "margin-10");
      } else {
        input.classList.add(`${p.element}-${this.id}`, "margin-10");
      }
      container.appendChild(input);
    });

    const kat = document.querySelector(`.select-${this.id}`);

    this.kategorije.forEach((k) => {
      let option = document.createElement("option");
      option.innerHTML = k;
      option.value = k;
      kat.appendChild(option);
    });
  }

  drawProdavnica(container) {
    const prodavnicaDiv = document.createElement("div");
    prodavnicaDiv.classList.add("prodavnica-div");
    container.appendChild(prodavnicaDiv);

    this.ime = document.createElement("p");
    this.ime.innerHTML = `Prodavnica: ${this.naziv}`;
    this.ime.style.fontWeight = "bolder";
    this.ime.style.alignSelf = "center";

    this.drawProizvodi(prodavnicaDiv);
  }

  drawProizvodi(container) {
    container.replaceChildren();
    container.appendChild(this.ime);

    this.proizvodi.forEach((p) => {
      let proizvodDiv = document.createElement("div");
      proizvodDiv.classList.add(`proizvod-div-${p.popisID}`);
      container.appendChild(proizvodDiv);

      let btnDiv = document.createElement("div");
      btnDiv.classList.add("btn-div");
      proizvodDiv.appendChild(btnDiv);

      let btnProdaj = document.createElement("input");
      btnProdaj.type = "submit";
      btnProdaj.value = "Prodaj";
      btnProdaj.classList.add("btn-prodaj");
      btnDiv.appendChild(btnProdaj);

      let kolicinaDiv = document.createElement("div");
      kolicinaDiv.classList.add(`kolicina-div-${p.popisID}`);
      proizvodDiv.appendChild(kolicinaDiv);

      let lbl1 = document.createElement("label");
      lbl1.innerHTML = "Kolicina:";
      kolicinaDiv.appendChild(lbl1);

      let input = document.createElement("input");
      input.type = "number";
      kolicinaDiv.appendChild(input);

      let prviDiv = document.createElement("div");
      prviDiv.classList.add("prvi-div");
      proizvodDiv.appendChild(prviDiv);

      let lbl = document.createElement("label");
      lbl.classList.add(`lbl-${p.popisID}`);
      lbl.innerHTML = `${p.proizvodNaziv}: ${p.proizvodKolicina}`;
      prviDiv.appendChild(lbl);

      let statusDiv = document.createElement("div");
      statusDiv.classList.add(`status-div-${p.popisID}`);
      statusDiv.style.width = `${p.proizvodKolicina}%`;
      statusDiv.style.height = "20px";
      statusDiv.style.border = "2px dashed black";
      statusDiv.style.backgroundColor = "blue";
      prviDiv.appendChild(statusDiv);
    });
  }

  getProizvodi = async () => {
    //https://localhost:7080/Proizvod/PreuzmiProizvode/1/Igracka
    let url = `https://localhost:7080/Proizvod/PreuzmiProizvode/${this.id}/`;
    const selectKAT = document.querySelector(`.select-${this.id}`).value;
    url += selectKAT;
    console.log(url);
  };
}
