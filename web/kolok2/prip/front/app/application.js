import { Student } from "./student.js";

export class Application {
  constructor(predmeti) {
    this.predmeti = predmeti;
    this.polja = [
      { naziv: "Broj indeksa:", klasa: "indeks" },
      { naziv: "Ime i prezime:", klasa: "imeiprezime" },
      { naziv: "Predmet:", klasa: "predmet" },
      { naziv: "Ocena:", klasa: "ocena" },
    ];
    this.colors = ["#dc2392", "#5c20df", "#11ee1e", "#fe9a01"];

    this.activePredmeti = [];
    this.studenti = [];
    this.oceneContainer = null;
  }

  draw(container) {
    const leviDiv = document.createElement("div");
    leviDiv.classList.add("levi-div");
    container.appendChild(leviDiv);
    this.drawPredmeti(leviDiv);
    this.oceneContainer = document.createElement("div");
    this.oceneContainer.classList.add("ocene");
    leviDiv.appendChild(this.oceneContainer);

    const desniDiv = document.createElement("div");
    desniDiv.classList.add("desni-div");
    container.appendChild(desniDiv);
    this.drawForm(desniDiv);
  }

  drawOcene() {
    this.studenti.forEach((p) => {
      p.drawOcene(this.oceneContainer);
    });
  }

  drawPredmeti(container) {
    const predmetiDiv = document.createElement("div");
    predmetiDiv.classList.add("predmeti");
    container.appendChild(predmetiDiv);

    this.predmeti.forEach((p, index) => {
      let predmet = document.createElement("div");
      predmetiDiv.appendChild(predmet);

      let cb = document.createElement("input");
      cb.type = "checkbox";
      cb.classList.add(`cb-${p.id}`);
      cb.onchange = this.onChangePreuzmi;
      predmet.appendChild(cb);

      let lbl = document.createElement("label");
      lbl.classList.add(`lbl-${p.id}`);
      lbl.innerHTML = p.naziv;
      lbl.style.color = this.colors[index % this.colors.length];
      predmet.appendChild(lbl);
    });
  }

  onChangePreuzmi = async () => {
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
    this.studenti = [];
    result.forEach((r) => {
      let idx = this.studenti.findIndex((p) => p.ime == r.student.imePrezime);
      if (idx == -1) {
        let student = new Student(r.student.imePrezime, () => {
          return this.activePredmeti.map((p) => {
            return {
              id: p,
              color: document.querySelector(`.lbl-${p}`).style.color,
            };
          });
        });
        this.studenti.push(student);
        idx = this.studenti.length - 1;
      }
      this.studenti[idx].ocene.push({
        pid: r.predmet.id,
        ocena: r.vrednost,
      });
    });
    this.oceneContainer.replaceChildren();
    this.drawOcene();
  };

  drawForm(container) {
    this.polja.forEach((p) => {
      let lbl = document.createElement("label");
      lbl.innerHTML = p.naziv;
      lbl.classList.add("margin-10");
      container.appendChild(lbl);

      let input = document.createElement("input");
      input.classList.add(p.klasa, "margin-10");
      container.appendChild(input);
    });
    const btnUpisi = document.createElement("input");
    btnUpisi.type = "button";
    btnUpisi.value = "Upisi";
    btnUpisi.classList.add("margin-10", "btn-upisi");
    btnUpisi.onclick = this.onClickUpisi;
    container.appendChild(btnUpisi);
  }

  onClickUpisi = async () => {
    const params = this.polja.map(
      (p) => document.querySelector(`.${p.klasa}`).value
    );
    const result = await fetch("http://localhost:5192/Ocene/DodajOcenu", {
      method: "POST",
      body: JSON.stringify({
        brojIndeksa: params[0],
        imePrezime: params[1],
        predmet: params[2],
        ocena: params[3],
      }),
      headers: {
        "content-type": "application/json",
      },
    })
      .then((response) => response.json())
      .catch((err) => console.error(err));
  };
}
