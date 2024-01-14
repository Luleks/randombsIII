import { Application } from "./application.js";

const podrucja = await fetch("https://localhost:7011/Podrucja/PreuzmiPodrcuja")
  .then((p) => p.json())
  .catch((err) => console.error(err));

const osobine = await fetch("https://localhost:7011/Osobine/PreuzmiOsobine")
  .then((p) => p.json())
  .catch((err) => console.error(err));

const app = new Application(podrucja, osobine);

app.draw(document.body);
