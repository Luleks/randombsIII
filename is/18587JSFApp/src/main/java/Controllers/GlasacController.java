package Controllers;

import java.util.List;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;

import BusinessLogic.GlasacLogic;
import Model.Glasac;

@ManagedBean
@ViewScoped
public class GlasacController {
	private int id;
	private String jmbg;
	private String ime;
	private String prezime;
	private boolean funkcioner;
	private boolean glasao;
	
	@EJB
	private GlasacLogic glasacLogic;
	
	public GlasacController() {
		
	}

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
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
    
    public void addGlasac() {
    	glasacLogic.addGlasac(jmbg, ime, prezime, funkcioner, glasao);
    }
    
    public void updateGlasao(int id) {
    	glasacLogic.updateGlasao(id);
    }
    
    public void removeGlasac(int id) {
    	glasacLogic.removeGlasac(id);
    }
    
    public void getGlasac(int id) {
    	Glasac glasac = glasacLogic.getGlasac(id);
    	this.funkcioner = glasac.isFunkcioner();
    	this.glasao = glasac.isGlasao();
    	this.jmbg = glasac.getJmbg();
    	this.ime = glasac.getIme();
    	this.prezime = glasac.getPrezime();
    	this.id = glasac.getID();
    }
    
    public void getGlasacByJmbg(String jmbg) {
    	Glasac glasac = glasacLogic.getGlasacByJmbg(jmbg);
    	this.funkcioner = glasac.isFunkcioner();
    	this.glasao = glasac.isGlasao();
    	this.jmbg = glasac.getJmbg();
    	this.ime = glasac.getIme();
    	this.prezime = glasac.getPrezime();
    	this.id = glasac.getID();
    }
    
    public List<Glasac> getGlasaci() {
    	return glasacLogic.getGlasaci();
    }
    
    public Long countGlasaci() {
    	return glasacLogic.countGlasaci();
    }
}
