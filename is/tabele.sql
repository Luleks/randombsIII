CREATE TABLE Stranke (
	strankaId INT NOT NULL,
    nazivStranke VARCHAR(50) NOT NULL,
    nosilacListe VARCHAR(50) NOT NULL,
    skupljeniPotpisi INT NOT NULL,
    brojClanova INT NOT NULL,
    PRIMARY KEY(strankaId)
);

CREATE TABLE id_gen (
	genName VARCHAR(50) NOT NULL,
    genVal INT NOT NULL,
    PRIMARY KEY(genName)
);

CREATE TABLE Glasac (
	glasacID INT NOT NULL,
	jmbg CHAR(13) NOT NULL,
    ime VARCHAR(20) NOT NULL,
    prezime VARCHAR(20) NOT NULL,
    funkcioner BOOLEAN NOT NULL,
    glasao BOOLEAN NOT NULL,
	PRIMARY KEY(glasacID)
);

CREATE TABLE GlasackiListic (
	listicID INT NOT NULL,
    izabranaStranka INT NOT NULL,
    PRIMARY KEY(listicID),
    FOREIGN KEY(izabranaStranka) REFERENCES Stranke(strankaID)
);