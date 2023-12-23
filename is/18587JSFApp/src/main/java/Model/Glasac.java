package Model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.TableGenerator;


@Entity
@Table(name="Glasac")
public class Glasac {
	@TableGenerator(name="glasacGen", table="id_gen", pkColumnName="genName", valueColumnName="genVal",
			allocationSize=1, pkColumnValue="glasacGen")
	@Id
	@Column(name="glasacId")
	@GeneratedValue(strategy = GenerationType.TABLE, generator="glasacGen")
	private int ID;
	
	@Column(name="jmbg")
	private String jmbg;
	
	@Column(name="ime")
	private String ime;
	
	@Column(name="prezime")
	private String prezime;
	
	@Column(name="funkcioner")
	private boolean funkcioner;
	
	@Column(name="glasao")
	private boolean glasao;
	
	public Glasac() {
		
	}
	
	public Glasac(String Jmbg, String Ime, String Prezime, boolean Funkcioner, boolean Glasao) {
		jmbg = Jmbg;
		ime = Ime;
		prezime = Prezime;
		funkcioner = Funkcioner;
		glasao = Glasao;
	}

    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public String getJmbg() {
        return jmbg;
    }

    public void setJmbg(String jmbg) {
        this.jmbg = jmbg;
    }

    public String getIme() {
        return ime;
    }

    public void setIme(String ime) {
        this.ime = ime;
    }

    public String getPrezime() {
        return prezime;
    }

    public void setPrezime(String prezime) {
        this.prezime = prezime;
    }

    public boolean isFunkcioner() {
        return funkcioner;
    }

    public void setFunkcioner(boolean funkcioner) {
        this.funkcioner = funkcioner;
    }

    public boolean isGlasao() {
        return glasao;
    }

    public void setGlasao(boolean glasao) {
        this.glasao = glasao;
    }
	
}
