import { Student } from "./student.js";

export class Application {
  constructor(predmeti) {
    this.predmeti = predmeti;
    this.polja = [
      { lbl: "Broj indeksa:", dd: "indeks" },
      { lbl: "Ime i prezime: ", dd: "imeprezime" },
      { lbl: "Predmet: ", dd: "predmet" },
      { lbl: "Ocena: ", dd: "ocena" },
    ];
    this.colors = ["#dc2392", "#5c20df", "#11ee1e", "#fe9a01"];

    this.activePredmeti = [];
    this.studenti = [];
    this.studentDiv = null;
  }

  draw(container) {
    const mainDiv = document.createElement("div");
    mainDiv.classList.add("main-div");
    container.appendChild(mainDiv);

    const leviDiv = document.createElement("div");
    leviDiv.classList.add("levi-div");
    mainDiv.appendChild(leviDiv);
    this.drawPredmeti(leviDiv);

    this.studentDiv = document.createElement("div");
    this.studentDiv.classList.add("student-div");
    leviDiv.appendChild(this.studentDiv);

    const desniDiv = document.createElement("div");
    desniDiv.classList.add("desni-div");
    mainDiv.appendChild(desniDiv);
    this.drawSearch(desniDiv);
  }

  drawPredmeti(container) {
    const predmetiDiv = document.createElement("div");
    predmetiDiv.classList.add("predmeti-div");
    container.appendChild(predmetiDiv);

    this.predmeti.forEach((p, idx) => {
      let predmetDiv = document.createElement("div");
      predmetiDiv.appendChild(predmetDiv);

      let cb = document.createElement("input");
      cb.classList.add(`cb-${p.id}`);
      cb.type = "checkbox";
      cb.onchange = this.onCheckChange;
      predmetDiv.appendChild(cb);

      let lbl = document.createElement("label");
      lbl.innerHTML = p.naziv;
      lbl.classList.add(`lbl-${p.id}`);
      lbl.style.color = this.colors[idx % this.colors.length];
      predmetDiv.appendChild(lbl);
    });
  }

  drawStudenti(container) {
    container.replaceChildren();
    this.studenti.forEach((p) => p.draw(container));
  }

  onCheckChange = async () => {
    this.studenti = [];
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

    result.forEach((r) => {
      let idx = this.studenti.findIndex((p) => p.ime == r.student.imePrezime);
      if (idx == -1) {
        this.studenti.push(
          new Student(r.student.imePrezime, this.getActivePredmeti)
        );
        idx = this.studenti.length - 1;
      }
      this.studenti[idx].ocene.push({
        predmet: r.predmet.id,
        ocena: r.vrednost,
      });

      this.drawStudenti(this.studentDiv);
    });
  };

  getActivePredmeti = () => {
    return this.activePredmeti.map((p) => {
      return {
        predmet: p,
        color: document.querySelector(`.lbl-${p}`).style.color,
      };
    });
  };

  drawSearch(container) {
    this.polja.forEach((p) => {
      let lbl = document.createElement("label");
      lbl.classList.add("margin-10");
      lbl.innerHTML = p.lbl;
      container.appendChild(lbl);

      let dd = document.createElement("input");
      dd.classList.add("margin-10", `dd-${p.dd}`);
      container.appendChild(dd);
    });
    const btnUpisi = document.createElement("input");
    btnUpisi.type = "button";
    btnUpisi.value = "Upisi";
    btnUpisi.classList.add("margin-10", "btn-upisi");
    container.appendChild(btnUpisi);
  }
}
