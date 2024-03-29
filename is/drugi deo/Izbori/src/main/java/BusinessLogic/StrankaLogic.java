package BusinessLogic;

import Model.Stranka;
import java.util.List;

public interface StrankaLogic {
	public boolean addStranka(String Naziv, String NosilacListe, int SkupljeniPotpisi, int BrojClanova);
	public boolean removeStranka(int id);
	public Stranka getStranka(int id);
	public Stranka getStrankaByNaziv(String Naziv);
	public List<Stranka> getStranke();
	public List<Integer> getStrankaIds();
	public boolean dodajPotpis(int id);
}
