export class Biljka {
  constructor(id, naziv, slika, brVidj) {
    this.id = id;
    this.naziv = naziv;
    this.slika = slika;
    this.brVidj = brVidj;
  }
  draw(container) {
    const biljkaDiv = document.createElement("div");
    biljkaDiv.classList.add("biljka-div", "margin-10");
    container.appendChild(biljkaDiv);

    const btnVidjena = document.createElement("button");
    btnVidjena.classList.add(`btn-vidjena-${this.id}`);
    btnVidjena.style.width = "100%";
    btnVidjena.innerHTML = "Vidjena";
    biljkaDiv.appendChild(btnVidjena);
    btnVidjena.onclick = this.onClickVidjena;

    const brVidj = document.createElement("p");
    brVidj.classList.add(`vidj-${this.id}`);
    brVidj.innerHTML = `Broj vidjenja: ${this.brVidj}`;
    biljkaDiv.appendChild(brVidj);

    const naziv = document.createElement("p");
    naziv.innerHTML = this.naziv;
    naziv.style.textAlign = "center";
    naziv.style.margin = "0px";
    biljkaDiv.appendChild(naziv);

    const slika = document.createElement("img");
    slika.src = this.slika;
    slika.alt = "Fali slika";
    slika.style.flexGrow = "1";
    biljkaDiv.appendChild(slika);
  }

  onClickVidjena = async () => {
    await fetch("https://localhost:7011/Biljke/UpisiVidjenje/1/1", {
      method: "POST",
      body: {
        latitude: 90,
        longitude: 180,
        datumIVreme: "2024-01-10T20:28:23.472Z",
      },
      headers: {
        "Content-Type": "application/json",
      },
    })
      .then((response) => response.json())
      .catch((err) => console.error(err));

    const vidj = document.querySelector(`.vidj-${this.id}`);
    this.brVidj += 1;
    vidj.innerHTML = `Broj vidjenja: ${this.brVidj}`;

    const btn = document.querySelector(`.btn-vidjena-${this.id}`);
    btn.disabled = true;
  };
}
