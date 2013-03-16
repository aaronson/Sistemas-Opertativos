package sisop;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Implementacion de un scheduler 
 * Round Robin. Esta clase esta vacia
 */ 
class RR extends Scheduler {

	private int quantum = DEFAULT_QUANTUM;

	/**
	 * Valor del quantum por defecto.
	 */
	public static final int DEFAULT_QUANTUM = 5;
	private int current_time;
	private Queue<Task> robins = new LinkedList<Task>();
	private LinkedList<String> finished_tasks;
	private int this_quantum_time;
	private int context;
	private boolean termino;

	/**
	 * Construye un planificador Round Robin
	 */ 
	RR() {
		super("RR");
	}

	/**
	 * Permite indicar el valor del quantum
	 * deseado para la planificacion
	 */
	public void set_quantum(int q) {
		this.quantum = q;
	}

	protected void scheduler_init() {

		current_time = -1;
		this_quantum_time = 0;
		this.finished_tasks = new LinkedList<String>();
		context =0;
		termino = false;
	}


	public String scheduler_next() {

		String res="";
		if (task_set.size()==finished_tasks.size())      
			return null;

		current_time++;


		List<String> incoming_tasks = task_set.get_released_tasks_at(current_time);

		for (String task_name: incoming_tasks) 
			this.robins.add(task_set.get(task_name));


		if (context > 0){
			if (!termino){
				Task cambia = robins.poll();
				robins.add(cambia);
			}
			res =  CONTEXT_SWITCH;
			context = 0;
			this_quantum_time = 0;
			termino = false;
		}else{
			if (!robins.isEmpty()){
				if (robins.peek().ttime == robins.peek().ptime){
					finished_tasks.add(robins.peek().name);
					robins.remove();
					if (!robins.isEmpty()){
						if (robins.peek().ttime > 0){
							context++;
							res = CONTEXT_SWITCH;
							termino = true;
						}else{
							robins.peek().ttime++;
							this_quantum_time=1;
						}
					}
				}else{
					if (this_quantum_time == quantum){
						if(robins.size()>1){
							context++;
							res =  CONTEXT_SWITCH;
						}
						this_quantum_time = 0;
					}else{
						robins.peek().ttime++;
						this_quantum_time++;
					}
				}
			}else{
				this_quantum_time = 0;
			}
			if (!res.equals(CONTEXT_SWITCH)){
				if (robins.isEmpty()){
					res =  IDLE_TASK;
				}else{
					res =  robins.peek().name;
				}
			}
		}
		for (Task task: robins){
			if (!task.name.equals(res) && finished_tasks.indexOf(task.name) == -1 ){
				task.wtime++;
			}
		}
		if (task_set.size()==finished_tasks.size())      
			return null;
		return res;
	}

}
