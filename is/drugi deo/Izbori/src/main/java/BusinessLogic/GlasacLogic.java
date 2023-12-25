package BusinessLogic;

import Model.Glasac;
import java.util.List;

public interface GlasacLogic {
	public boolean addGlasac(String Jmbg, String Ime, String Prezime, boolean Funkcioner, boolean Glasao);
	public boolean updateGlasao(int id);
	public boolean removeGlasac(int id);
	public Glasac getGlasac(int id);
	public Glasac getGlasacByJmbg(String jmbg);
	public List<Glasac> getGlasaci();
	public Long countGlasaci();
}
