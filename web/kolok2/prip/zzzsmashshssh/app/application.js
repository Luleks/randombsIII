import { Student } from "./student.js";

export class Application {
  constructor(predmeti) {
    this.predmeti = predmeti;
    this.colors = ["#dc2392", "#5c20df", "#11ee1e", "#fe9a01"];
    this.polja = [
      { lbl: "Broj indeksa:", klasa: "ind" },
      { lbl: "Ime i prezime:", klasa: "imeprezime" },
      { lbl: "Predmet:", klasa: "predmet" },
      { lbl: "Ocena:", klasa: "ocena" },
    ];

    this.activePredmeti = [];
    this.studenti = [];
    this.studentiDiv = null;
  }
  draw(container) {
    const mainDiv = document.createElement("div");
    mainDiv.classList.add("main-div");
    container.appendChild(mainDiv);

    const leviDiv = document.createElement("div");
    leviDiv.classList.add("levi-div");
    mainDiv.appendChild(leviDiv);
    this.drawLeviDiv(leviDiv);
    this.studentiDiv = document.createElement("div");
    this.studentiDiv.classList.add("studenti-div");
    leviDiv.appendChild(this.studentiDiv);

    const desniDiv = document.createElement("div");
    desniDiv.classList.add("desni-div");
    mainDiv.appendChild(desniDiv);
    this.drawForma(desniDiv);
  }

  onChangePrikazi = async () => {
    this.activePredmeti = this.predmeti
      .filter((p) => document.querySelector(`.cb-${p.id}`).checked)
      .map((p) => p.id);

    const result = await fetch("http://localhost:5192/Ocene/PreuzmiOcene", {
      method: "PUT",
      body: JSON.stringify(this.activePredmeti),
      headers: {
        "Content-Type": "application/json",
      },
    })
      .then((response) => response.json())
      .catch((err) => console.error(err));

    this.studentiDiv.replaceChildren();
    this.studenti = [];

    result.forEach((r) => {
      let idx = this.studenti.findIndex((p) => p.id == r.student.id);
      if (idx == -1) {
        this.studenti.push(
          new Student(
            r.student.id,
            r.student.imePrezime,
            this.getActivePredmeti
          )
        );
        idx = this.studenti.length - 1;
      }
      this.studenti[idx].ocene.push({
        predmet: r.predmet.id,
        ocena: r.vrednost,
      });
    });

    this.studenti.forEach((s) => s.draw(this.studentiDiv));
  };

  getActivePredmeti = () => {
    return this.activePredmeti.map((p) => {
      return { id: p, color: document.querySelector(`.lbl-${p}`).style.color };
    });
  };

  drawPredmeti(container) {
    this.predmeti.forEach((p, index) => {
      let predmetDiv = document.createElement("div");
      predmetDiv.classList.add("predmet-list");
      container.appendChild(predmetDiv);

      let cb = document.createElement("input");
      cb.type = "checkbox";
      cb.onchange = this.onChangePrikazi;
      cb.classList.add(`cb-${p.id}`);
      predmetDiv.appendChild(cb);

      let lbl = document.createElement("label");
      lbl.innerHTML = p.naziv;
      lbl.classList.add(`lbl-${p.id}`);
      lbl.style.color = this.colors[index % this.colors.length];
      predmetDiv.appendChild(lbl);
    });
  }

  drawLeviDiv(container) {
    const predmetiDiv = document.createElement("div");
    predmetiDiv.classList.add("predmeti-div");
    container.appendChild(predmetiDiv);
    this.drawPredmeti(predmetiDiv);
  }

  drawForma(container) {
    this.polja.forEach((p) => {
      let lbl = document.createElement("label");
      lbl.innerHTML = p.lbl;
      lbl.classList.add("margin-10");
      container.appendChild(lbl);

      let input = document.createElement("input");
      input.classList.add(`input-${p.klasa}`, "margin-10");
      container.appendChild(input);
    });

    const btnUpisi = document.createElement("input");
    btnUpisi.type = "submit";
    btnUpisi.onclick = this.onClickUpisi;
    btnUpisi.value = "Upisi";
    btnUpisi.classList.add("btn-upisi", "margin-10");
    container.appendChild(btnUpisi);
  }

  onClickUpisi = async () => {
    alert("onClickUpisi");
  };
}
