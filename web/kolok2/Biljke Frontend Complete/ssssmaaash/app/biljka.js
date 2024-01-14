export class Biljka {
  constructor(id, naziv, slika, brVidjenja) {
    this.id = id;
    this.naziv = naziv;
    this.slika = slika;
    this.brVidjenja = brVidjenja;
  }

  draw(container) {
    const biljkaDiv = document.createElement("div");
    biljkaDiv.classList.add("biljka-div");

    const slika = document.createElement("img");
    slika.src = this.slika;
    biljkaDiv.appendChild(slika);

    const naziv = document.createElement("p");
    naziv.innerHTML = this.naziv;
    naziv.style.textAlign = "center";
    biljkaDiv.appendChild(naziv);

    const brvidj = document.createElement("p");
    brvidj.classList.add(`vidj-${this.id}`);
    brvidj.innerHTML = `Broj vidjenja: ${this.brVidjenja}`;
    biljkaDiv.appendChild(brvidj);

    const btnVidjena = document.createElement("button");
    btnVidjena.classList.add("btn-vidjena", `btn-vidjena-${this.id}`);
    btnVidjena.innerHTML = "Vidjena";
    btnVidjena.onclick = this.onClickVidjena;
    biljkaDiv.appendChild(btnVidjena);

    container.appendChild(biljkaDiv);
  }

  onClickVidjena = async () => {
    let url = `https://localhost:7011/Biljke/UpisiVidjenje/${this.id}/${
      document.querySelector(".podrucje-dd").value
    }`;

    await fetch(url, {
      method: "POST",
      body: JSON.stringify({
        latitude: 90,
        longitude: 180,
        datumIVreme: "2024-01-07T09:22:28.486Z",
      }),
      headers: {
        "Content-Type": "application/json",
      },
    });

    this.brVidjenja += 1;
    const lblVidjena = document.querySelector(`.vidj-${this.id}`);
    lblVidjena.innerHTML = `Broj vidjenja: ${this.brVidjenja}`;
    const btnVidjena = document.querySelector(`.btn-vidjena-${this.id}`);
    btnVidjena.disabled = true;
  };
}
