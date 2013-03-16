package sisop;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Random;

class MFQIO extends Scheduler {

	public static final int QUANTUM_H = 5;
	public static final int QUANTUM_M = 15;
	public static final int QUANTUM_L = 45;


	private int current_time;
	private Queue<Task> robinh = new LinkedList<Task>();
	private Queue<Task> robinm = new LinkedList<Task>();
	private Queue<Task> robinl = new LinkedList<Task>();

	private LinkedList<String> finished_tasks;
	private int this_quantum_time;
	private int actual_queue;
	private int context;
	private int quantum;
	private boolean no_necesito_cambio;
	private boolean subime;

	public MFQIO() {
		super("MFQIO");
	}

	protected void scheduler_init() {
		current_time = -1;
		this_quantum_time = 0;
		this.finished_tasks = new LinkedList<String>();
		context =0;
		actual_queue = 1;

		subime = false;
	}

	public String scheduler_next() {

		Random rand = new Random();

		String res="";
		if (task_set.size()==finished_tasks.size())      
			return null;

		current_time++;

		List<String> incoming_tasks = task_set.get_released_tasks_at(current_time);

		for (String task_name: incoming_tasks) 
			this.robinh.add(task_set.get(task_name));

		if (actual_queue == 1){
			quantum = QUANTUM_H;
		}else if (actual_queue == 2){
			quantum = QUANTUM_M;
		}else{
			quantum = QUANTUM_L;
		}


		if (context > 0){
			if (actual_queue == 1){
				if (!subime){
					if (!no_necesito_cambio){
						Task cambia = robinh.poll();
						robinm.add(cambia);
					}
				}else {
					Task cambia = robinh.poll();
					robinh.add(cambia);
				}
				res =  CONTEXT_SWITCH;
				context = 0;
				this_quantum_time = 0;
			}else if (actual_queue == 2){
				if (subime){
					Task cambia = robinm.poll();
					robinh.add(cambia);
				}else{
					if (!no_necesito_cambio){
						Task cambia = robinm.poll();
						robinl.add(cambia);
					}
				}
				res =  CONTEXT_SWITCH;
				context = 0;
				this_quantum_time = 0;
			}else{
				if (subime){
					Task cambia = robinl.poll();
					robinm.add(cambia);
				}else{
					if (!no_necesito_cambio){
						Task cambia = robinl.poll();
						robinl.add(cambia);
					}
				}
				res =  CONTEXT_SWITCH;
				context = 0;
				this_quantum_time = 0;
			}
			no_necesito_cambio = false;

		}else{
			if (!robinh.isEmpty()){
				if (robinh.peek().ttime == robinh.peek().ptime){
					finished_tasks.add(robinh.peek().name);
					robinh.remove();
					res = elegirPila();
				}else{
					if (this_quantum_time == quantum){
						if(robinh.size() > 1){
							context++;
							res =  CONTEXT_SWITCH;
						}else{
							if (robinm.isEmpty()){
								Task cambia = robinh.poll();
								robinm.add(cambia);
								actual_queue = 2;
							}else{
								context++;
								res =  CONTEXT_SWITCH;
							}							
						}
						this_quantum_time = 0;
					}else{
						int io = rand.nextInt(2);
						int por = rand.nextInt(100);
						if (io == 1 && (100*this_quantum_time)/quantum > (por)){
							context++;
							res =  CONTEXT_SWITCH;
							subime = true;
						}else{
							robinh.peek().ttime++;
							this_quantum_time++;
						}
					}
				}
			}else if (!robinm.isEmpty()){
				if (robinm.peek().ttime == robinm.peek().ptime){
					finished_tasks.add(robinm.peek().name);
					robinm.remove();
					res = elegirPila();
				}else{
					if (this_quantum_time == quantum){
						if(!robinh.isEmpty() || robinm.size() > 1){
							context++;
							res =  CONTEXT_SWITCH;						
						}else if (robinl.isEmpty()){
							Task cambia = robinm.poll();
							robinl.add(cambia);
							actual_queue = 3;
						}else{
							context++;
							res =  CONTEXT_SWITCH;
						}
						this_quantum_time = 0;
					}else{
						robinm.peek().ttime++;
						this_quantum_time++;
					}
				}
			}else if (!robinl.isEmpty()){
				if (robinl.peek().ttime == robinl.peek().ptime){
					finished_tasks.add(robinl.peek().name);
					robinl.remove();
					elegirPila();
				}else{
					if (this_quantum_time == quantum){
						if(!robinh.isEmpty() || !robinm.isEmpty() || robinl.size() > 1){
							context++;
							res =  CONTEXT_SWITCH;						
						}
						this_quantum_time = 0;
					}else{
						robinl.peek().ttime++;
						this_quantum_time++;
					}
				}
			}else{
				this_quantum_time = 0;
			}

			if (!res.equals(CONTEXT_SWITCH)){
				if(robinh.isEmpty() && robinm.isEmpty() && robinl.isEmpty()){
					res =  IDLE_TASK;
				}else{
					if (!robinh.isEmpty()){
						res =  robinh.peek().name;
					}else if (!robinm.isEmpty()){
						res =  robinm.peek().name;
					}else{
						res =  robinl.peek().name;
					}
				}
			}
		}
		for (Task task: robinh){
			if (!task.name.equals(res) && finished_tasks.indexOf(task.name) == -1 ){
				task.wtime++;
			}
		}
		for (Task task: robinm){
			if (!task.name.equals(res) && finished_tasks.indexOf(task.name) == -1 ){
				task.wtime++;
			}
		}
		for (Task task: robinl){
			if (!task.name.equals(res) && finished_tasks.indexOf(task.name) == -1 ){
				task.wtime++;
			}
		}
		if (task_set.size()==finished_tasks.size())      
			return null;
		return res;
	}

	private String elegirPila (){
		String res = "";
		if (!robinh.isEmpty()){
			if (robinh.peek().ttime > 0){
				context++;
				res = CONTEXT_SWITCH;
				actual_queue = 1;
				no_necesito_cambio = true;
			}else{
				robinh.peek().ttime++;
				this_quantum_time=1;
				actual_queue = 1;
			}
		}else if (!robinm.isEmpty()){
			if (robinm.peek().ttime > 0){
				context++;
				res = CONTEXT_SWITCH;
				actual_queue = 2;
				no_necesito_cambio = true;
			}else{
				robinm.peek().ttime++;
				this_quantum_time=1;
				actual_queue = 2;
			}
		}else if (!robinl.isEmpty()){
			if (robinl.peek().ttime > 0){
				context++;
				res = CONTEXT_SWITCH;
				actual_queue = 3;
				no_necesito_cambio = true;				
			}else{
				robinl.peek().ttime++;
				this_quantum_time=1;
				actual_queue = 3;
			}
		}else{
			res = IDLE_TASK;
		}		
		return res;
	}
}
