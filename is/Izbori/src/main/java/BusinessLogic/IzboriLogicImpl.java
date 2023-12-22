package BusinessLogic;

import Model.Stranka;

import javax.ejb.Remote;
import javax.ejb.Stateless;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

@Remote(IzboriLogic.class)
@Stateless
public class IzboriLogicImpl implements IzboriLogic {

	private EntityManager em;
	
	public IzboriLogicImpl() {
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("IzboriPU");
		em = emf.createEntityManager();
	}
	
	@Override
	public Stranka proglasiPobednika() {
		// TODO Auto-generated method stub
		return null;
	}

}
