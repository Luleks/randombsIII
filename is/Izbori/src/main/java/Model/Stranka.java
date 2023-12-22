package Model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.TableGenerator;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Table;
import javax.persistence.Id;

@Entity
@Table(name="Stranke")
public class Stranka {
	@TableGenerator(name="strankaGen", table="id_gen", pkColumnName="genName", valueColumnName="genVal",
			allocationSize=1, pkColumnValue="strankaGen")
	@Id
	@GeneratedValue(strategy = GenerationType.TABLE, generator="strankaGen")
	private int ID;
	
	@Column(name="nazivStranke")
	private String naziv;
	
	@Column(name="nosilacListe")
	private String nosilacListe;
	
	@Column(name="skupljeniPotpisi")
	private int skupljeniPotpisi;
	
	@Column(name="brojClanova")
	private int brojClanova;
	
	public Stranka() {
		
	}
	
	public Stranka(String Naziv, String NosilacListe, int SkupljeniPotpisi, int BrojClanova) {
		naziv = Naziv;
		nosilacListe = NosilacListe;
		skupljeniPotpisi = SkupljeniPotpisi;
		brojClanova = BrojClanova;
	}

    public int getID() {
        return ID;
    }

    public String getNaziv() {
        return naziv;
    }

    public String getNosilacListe() {
        return nosilacListe;
    }

    public int getSkupljeniPotpisi() {
        return skupljeniPotpisi;
    }

    public int getBrojClanova() {
        return brojClanova;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public void setNosilacListe(String nosilacListe) {
        this.nosilacListe = nosilacListe;
    }

    public void setSkupljeniPotpisi(int skupljeniPotpisi) {
        this.skupljeniPotpisi = skupljeniPotpisi;
    }

    public void setBrojClanova(int brojClanova) {
        this.brojClanova = brojClanova;
    }
	
	
}
