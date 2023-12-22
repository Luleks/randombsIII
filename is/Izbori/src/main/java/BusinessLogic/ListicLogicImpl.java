package BusinessLogic;

import java.util.List;

import Model.Stranka;
import Model.Glasac;
import Model.GlasackiListic;

import BusinessLogic.StrankaLogicImpl;

import javax.ejb.Remote;
import javax.ejb.Stateless;

import javax.persistence.TypedQuery;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

@Stateless
@Remote(ListicLogic.class)
public class ListicLogicImpl implements ListicLogic {
	
	private EntityManager em;
	private StrankaLogicImpl sli;
	
	public ListicLogicImpl() {
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("IzboriPU");
		em = emf.createEntityManager();
		
		sli = new StrankaLogicImpl();
	}

	@Override
	public boolean dodajListic(int brStranke) {
		try {
			em.getTransaction().begin();
			GlasackiListic listic = null;
			Stranka stranka = sli.getStranka(brStranke);
			if (stranka == null)
				listic = new GlasackiListic(-1);
			else
				listic = new GlasackiListic(brStranke);
			em.persist(listic);
			em.getTransaction().commit();
			return true;
		}
		catch (Exception ec) {
			return false;
		}
	}

	@Override
	public int countIzlaznost() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int countGlasovi(int brStranke) {
		// TODO Auto-generated method stub
		return 0;
	}

}
