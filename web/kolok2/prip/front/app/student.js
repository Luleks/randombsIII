export class Student {
  constructor(ime, getActivePredmeti) {
    this.ime = ime;
    this.ocene = [];
    this.getActivePredmeti = getActivePredmeti;
  }

  drawOcene(container) {
    const studDiv = document.createElement("div");
    studDiv.classList.add("student-ocene");
    container.appendChild(studDiv);

    const ime = document.createElement("p");
    ime.innerHTML = this.ime;
    ime.style.textAlign = "center";
    studDiv.appendChild(ime);

    const stuboviDiv = document.createElement("div");
    stuboviDiv.classList.add("stubovi");

    const activePredmeti = this.getActivePredmeti();

    const n_cols = activePredmeti.length;
    stuboviDiv.style.gridTemplateColumns = `repeat(${n_cols}, 1fr)`;
    studDiv.appendChild(stuboviDiv);

    activePredmeti.forEach((p) => {
      let stubDiv = document.createElement("div");
      let predmet = this.ocene.findIndex((r) => r.pid == p.id);
      if (predmet == -1) stubDiv.style.height = "0";
      else stubDiv.style.height = `${this.ocene[predmet].ocena * 10}%`;
      stubDiv.style.backgroundColor = p.color;
      stuboviDiv.appendChild(stubDiv);
    });
  }
}
