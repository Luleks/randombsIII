export class Prodavnica {
  constructor(id, naziv, kategorije, proizvodi) {
    this.id = id;
    this.naziv = naziv;
    this.kategorije = kategorije;
    this.proizvodi = proizvodi;
    this.polja = [
      { lbl: "Naziv:", klasa: "naziv", element: "input", type: "text" },
      { lbl: "Kategorija:", klasa: "kategorija", element: "select" },
      { lbl: "Cena:", klasa: "cena", element: "input", type: "number" },
      { lbl: "Kolicina:", klasa: "kolicina", element: "input", type: "number" },
    ];

    this.proizvodiDiv = null;
  }

  draw(container) {
    const formDiv = document.createElement("div");
    formDiv.classList.add("form-div");
    container.appendChild(formDiv);

    this.drawForm(formDiv);

    const prodajaDiv = document.createElement("div");
    prodajaDiv.classList.add("prodaja-div");
    container.appendChild(prodajaDiv);

    this.drawProdaja(prodajaDiv);
  }

  drawForm(container) {
    const innerFormDiv = document.createElement("div");
    innerFormDiv.classList.add("inner-form-div");
    container.appendChild(innerFormDiv);

    const title = document.createElement("p");
    title.classList.add("title");
    title.innerHTML = "Upis proizvoda";
    innerFormDiv.appendChild(title);

    this.drawPoljaForme(innerFormDiv);

    const btnDodajProizvod = document.createElement("button");
    btnDodajProizvod.classList.add("btn-dodaj-proizvod", "margin-5");
    btnDodajProizvod.innerHTML = "Dodaj proizvod";
    btnDodajProizvod.onclick = this.onClickDodajProizvod;
    innerFormDiv.appendChild(btnDodajProizvod);
  }

  drawPoljaForme(container) {
    this.polja.forEach((p) => {
      let lbl = document.createElement("label");
      lbl.innerHTML = p.lbl;
      lbl.classList.add("margin-5");
      container.appendChild(lbl);

      let input = document.createElement(p.element);
      if (p.type != undefined) {
        input.classList.add(`${p.type}-${p.klasa}-${this.id}`, "margin-5");
        input.type = p.type;
      } else {
        input.classList.add(`${p.element}-${p.klasa}-${this.id}`, "margin-5");
        input.onchange = this.onChangePromeni;
      }
      container.appendChild(input);
    });

    const select = document.querySelector(`.select-kategorija-${this.id}`);

    this.kategorije.forEach((k) => {
      let option = document.createElement("option");
      option.value = k;
      option.innerHTML = k;
      select.appendChild(option);
    });
  }

  onChangePromeni = async () => {
    this.proizvodi = await fetch(
      `https://localhost:7080/Proizvod/PreuzmiProizvode/${this.id}/${
        document.querySelector(`.select-kategorija-${this.id}`).value
      }`
    )
      .then((response) => response.json())
      .catch((err) => console.error(err));
    this.drawProizvodi(this.proizvodiDiv);
  };

  onClickDodajProizvod = async () => {
    // https://localhost:7080/Proizvod/DodajProizvod/1/25/120
    const cena = parseInt(
      document.querySelector(`.number-cena-${this.id}`).value
    );
    const kolicina = parseInt(
      document.querySelector(`.number-kolicina-${this.id}`).value
    );

    if (isNaN(cena) || isNaN(kolicina) || kolicina > 100) {
      alert("Nevalidna cena/kolicina ili je cena/kolicina > 100");
      return;
    }

    const naziv = document.querySelector(`.text-naziv-${this.id}`).value;
    const kategorija = document.querySelector(
      `.select-kategorija-${this.id}`
    ).value;

    if (naziv == "") {
      alert("Prazno je polje naziv");
    }

    let base = `https://localhost:7080/Proizvod/DodajProizvod/${this.id}/${cena}/${kolicina}`;

    const result = await fetch(base, {
      method: "POST",
      body: JSON.stringify({
        naziv: naziv,
        kategorija: kategorija,
      }),
      headers: {
        "Content-Type": "application/json",
      },
    })
      .then((response) => response.json())
      .catch((err) => console.error(err));

    this.onChangePromeni();
    alert(result);
  };

  drawProdaja(container) {
    const title = document.createElement("p");
    title.classList.add("title2");
    title.innerHTML = `Prodavnica: ${this.naziv}`;
    container.appendChild(title);

    this.proizvodiDiv = document.createElement("div");
    this.proizvodiDiv.classList.add("inner-prodaja-div");
    container.appendChild(this.proizvodiDiv);

    this.drawProizvodi(this.proizvodiDiv);
  }

  drawProizvodi(container) {
    container.replaceChildren();
    this.proizvodi.forEach((p) => {
      let proizvodDiv = document.createElement("div");
      proizvodDiv.classList.add("proizvod-div");
      container.appendChild(proizvodDiv);

      let btnDiv = document.createElement("div");
      btnDiv.classList.add("btn-prodaja-div");
      proizvodDiv.appendChild(btnDiv);

      let btnProdaj = document.createElement("button");
      btnProdaj.classList.add(`btn-prodaj-${p.popisID}`);
      btnProdaj.onclick = this.onClickProdaj;
      btnProdaj.innerHTML = "Prodaj";
      btnDiv.appendChild(btnProdaj);

      let kolicinaDiv = document.createElement("div");
      kolicinaDiv.classList.add(`kolicina-div`);
      proizvodDiv.appendChild(kolicinaDiv);

      let lbl = document.createElement("label");
      lbl.innerHTML = "Kolicina: ";
      kolicinaDiv.appendChild(lbl);

      let kolicinaInput = document.createElement("input");
      kolicinaInput.type = "number";
      kolicinaInput.classList.add(`kolicina-input-${p.popisID}`);
      kolicinaDiv.appendChild(kolicinaInput);

      let statsDiv = document.createElement("div");
      statsDiv.classList.add("stats-div");
      proizvodDiv.appendChild(statsDiv);

      let lblStats = document.createElement("label");
      lblStats.innerHTML = `${p.proizvodNaziv}:${p.proizvodKolicina}`;
      lblStats.classList.add(`lbl-${p.popisID}`);
      statsDiv.appendChild(lblStats);

      let stoDiv = document.createElement("div");
      stoDiv.classList.add("sto-div");
      statsDiv.appendChild(stoDiv);

      let procenatDiv = document.createElement("div");
      procenatDiv.classList.add("procenat-div");
      procenatDiv.style.width = `${p.proizvodKolicina}%`;
      procenatDiv.style.height = "100%";
      procenatDiv.style.backgroundColor = "red";
      stoDiv.appendChild(procenatDiv);
    });
  }

  onClickProdaj = async () => {};
}
