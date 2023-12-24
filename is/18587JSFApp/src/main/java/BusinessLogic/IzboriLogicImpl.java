package BusinessLogic;

import Model.Stranka;

import java.util.List;

import javax.ejb.EJB;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;


@Stateless
public class IzboriLogicImpl implements IzboriLogic {

	@PersistenceContext(name="IzboriPU")
	private EntityManager em;
	
	@EJB
	private StrankaLogic sli;
	
	@EJB
	private ListicLogic lli;
	
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
