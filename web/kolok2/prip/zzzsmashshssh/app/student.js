export class Student {
  constructor(id, naziv, getActivePredmeti) {
    this.id = id;
    this.naziv = naziv;
    this.ocene = [];
    this.getActivePredmeti = getActivePredmeti;
  }

  draw(container) {
    const studentDiv = document.createElement("div");
    studentDiv.classList.add("student-div");
    container.appendChild(studentDiv);

    const ime = document.createElement("p");
    ime.innerHTML = this.naziv;
    ime.style.textAlign = "center";
    studentDiv.appendChild(ime);

    const activePredmeti = this.getActivePredmeti();

    const oceneDiv = document.createElement("div");
    oceneDiv.classList.add("ocene-div");
    oceneDiv.style.gridTemplateColumns = `repeat(${activePredmeti.length}, 1fr)`;
    studentDiv.appendChild(oceneDiv);

    activePredmeti.forEach((p) => {
      let ocena = this.ocene.find((o) => o.predmet == p.id);
      let stubDiv = document.createElement("div");
      stubDiv.style.backgroundColor = p.color; 
      if (ocena == null) {
        stubDiv.style.height = "0%";
      } else {
        stubDiv.style.height = `${ocena.ocena * 10}%`;
      }
      oceneDiv.appendChild(stubDiv);
    });
  }
}
