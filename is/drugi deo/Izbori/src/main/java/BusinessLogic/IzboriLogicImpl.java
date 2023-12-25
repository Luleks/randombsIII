package BusinessLogic;

import Model.Stranka;

import java.util.List;

import javax.ejb.Remote;
import javax.ejb.Stateless;

@Remote(IzboriLogic.class)
@Stateless
public class IzboriLogicImpl implements IzboriLogic {

	private StrankaLogicImpl sli;
	private ListicLogicImpl lli;
	
	public IzboriLogicImpl() {
		sli = new StrankaLogicImpl();
		lli = new ListicLogicImpl();
	}
	
	@Override
	public Stranka proglasiPobednika() {
		int maxStrankaId = -1;
		long maxGlasova = 0;
		List<Integer> strankeIds = sli.getStrankaIds();
		for (Integer id : strankeIds) {
			long glasovi = lli.countGlasovi(id.intValue());
			if (glasovi > maxGlasova) {
				maxGlasova = glasovi;
				maxStrankaId = id;
			}
		}
		Stranka pobednik = sli.getStranka(maxStrankaId);
		return pobednik;
	}

}
