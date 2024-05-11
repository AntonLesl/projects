public class Fact extends NodeFact{



        private String sign;
        private final NodeFact fact;

        public Fact(String sign, NodeFact fact) {
            this.fact = fact;
        }

        public double eval(Environment env) throws EvalException {
            return fact.eval(env);
        }

        public String code() {
            return sign + fact.code();
        }

}
