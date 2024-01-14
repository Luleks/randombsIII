import { Application } from "./application.js";

const predmeti = await fetch("http://localhost:5192/Ocene/PreuzmiPredmete")
  .then((response) => response.json())
  .catch((err) => console.error(err));

const app = new Application(predmeti);

app.draw(document.body);
