package Model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.TableGenerator;

@Entity
@Table(name="GlasackiListic")
public class GlasackiListic {
	@TableGenerator(name="listicGen", table="id_gen", pkColumnName="genName", valueColumnName="genVal",
			allocationSize=1, pkColumnValue="listicGen")
	@Id
	@GeneratedValue(strategy = GenerationType.TABLE, generator="listicGen")
	private int ID;
	
	@Column(name="izabranaStranka")
	private int strankaID;
	
	public GlasackiListic() {
		
	}
	
	public GlasackiListic(int StrankaID) {
		strankaID = StrankaID;
	}
	
    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public int getStrankaID() {
        return strankaID;
    }

    public void setStrankaID(int strankaID) {
        this.strankaID = strankaID;
    }
	
}
