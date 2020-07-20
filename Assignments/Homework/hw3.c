//Brandon Truong

void psum4a(float a[], float p[], int cnt)
{
	long int i;
	float last_val, val;
	last_val = p[0] = a[0];
    //4 way unrolling
	for( i = 1; i < cnt - 3; i+=4) {
		p[i] = last_val + a[i];
		float temp1 = a[i] + a[i+1];
		p[i+1] = last_val + temp1;
		float temp2 = temp1 + a[i+2];
		p[i+2] = last_val + temp2;
		float temp3 = temp2 + a[i+3];
		val = last_val + temp3;
		p[i+3] = val;
		last_val = val;
	}
    //for anything not accounted for in previous loop
    for (; i < cnt; i++) {
        val  = last_val + a[i];
        p[i] = val;
        last_val = val;
    }
}
/*
Throughput and latency can limit the minimum CPE we can achieve.
Throughput is the limit of actions done in a period of time and latency is how long it takes to process an instruction.
We can use loop unrolling and reassociation in order to do multiple steps with a better instruction order.
If we overlap enough instructions, we can reach the throughput, or how many actions we can do in a certain time, bypassing latency.
*/
	