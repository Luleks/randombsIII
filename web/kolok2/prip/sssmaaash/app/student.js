export class Student {
  constructor(ime, getActivePredmeti) {
    this.ime = ime;
    this.ocene = [];
    this.getActivePredmeti = getActivePredmeti;
  }

  draw(container) {
    const studentDiv = document.createElement("div");
    studentDiv.classList.add("one-student-div");
    container.appendChild(studentDiv);

    const naziv = document.createElement("p");
    naziv.innerHTML = this.ime;
    studentDiv.appendChild(naziv);

    const predmeti = this.getActivePredmeti();

    const oceneDiv = document.createElement("div");
    oceneDiv.classList.add("ocene");
    oceneDiv.style.gridTemplateColumns = `repeat(${predmeti.length}, 1fr)`;
    studentDiv.appendChild(oceneDiv);

    predmeti.forEach((p) => {
      let div = document.createElement("div");
      let ocena = this.ocene.find((r) => r.predmet == p.predmet);
      if (ocena == null) div.style.height = "0px";
      else div.style.height = `${ocena.ocena * 10}%`;
      div.style.backgroundColor = p.color;
      oceneDiv.appendChild(div);
    });
  }
}
