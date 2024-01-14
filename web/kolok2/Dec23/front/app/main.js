import { Application } from "./application.js";

const prodavnice = await fetch(
  "https://localhost:7080/Prodavnica/PreuzmiProdavnice"
)
  .then((response) => response.json())
  .catch((err) => console.error(err));

const kategorije = await fetch(
  "https://localhost:7080/Proizvod/PrivabiKategorije"
)
  .then((response) => response.json())
  .catch((err) => console.error(err));

let proizvodi = new Map();
for (let prodavnica of prodavnice) {
  let proizvodi_ = await fetch(
    `https://localhost:7080/Proizvod/PreuzmiProizvode/${prodavnica.id}/Knjiga`
  )
    .then((response) => response.json())
    .catch((err) => console.error(err));
  proizvodi.set(prodavnica, proizvodi_);
}

const app = new Application(proizvodi, kategorije);

app.draw(document.body);
