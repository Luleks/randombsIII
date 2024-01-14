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

const prodavnice_proizvodi = new Map();

for (let prodavnica of prodavnice) {
  let proizvodi = await fetch(
    `https://localhost:7080/Proizvod/PreuzmiProizvode/${prodavnica.id}/${kategorije[0]}`
  )
    .then((response) => response.json())
    .catch((err) => console.error(err));
  prodavnice_proizvodi.set(prodavnica, proizvodi);
}

const app = new Application(prodavnice_proizvodi, kategorije);

app.draw(document.body);
