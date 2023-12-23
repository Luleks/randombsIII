package BusinessLogic;

import java.util.List;
import Model.GlasackiListic;

public interface ListicLogic {
	public boolean dodajListic(int brStranke, String glasacJmbg);
	public boolean dodajListic(String nazivStranke, String glasacJmbg);
	public double countIzlaznost();
	public int countGlasovi(int brStranke);
	public boolean removeListic(int listicID);
	public List<GlasackiListic> getListici();
}
