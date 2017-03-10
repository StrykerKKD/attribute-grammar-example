open Core.Std;

/**
 * Structure of the grammar.
 */

type v = float;
type l = float;
type r = float;

type attribute = 
  | Attribute (option v) (option l) (option r);

type dot = Dot;

type binary =
  | Zero attribute
  | One attribute;

type number =
  | N number binary attribute
  | Lambda attribute;

type start =
  | S number dot number attribute;

/**
 * Helper functions.
 */

let square_some = Option.map f::((**) 2.);

let add_some = Option.map2 f::(+.);

let add_one = Option.map f::((+.) 1.);

let negate_some = fun 
    | Some value => Some (-.value)
    | None => None;

let get_attribute_b = fun
    | Zero attribute => attribute
    | One attribute => attribute;

let get_attribute_n  = fun    
    | N _ _ attribute => attribute
    | Lambda attribute => attribute;

let get_v = fun
    | Attribute v _ _ => v;

let get_l = fun
    | Attribute _ l _ => l;

let get_r = fun 
    | Attribute _ _ r => r;

let update_attribute_value old_value new_value =>
    switch old_value {
        | None => new_value
        | _ => old_value
    }; 

let update_attribute old_attribute new_attribute => {
    let Attribute o_v o_l o_r = old_attribute;
    let Attribute n_v n_l n_r = new_attribute;
    Attribute 
        (update_attribute_value o_v n_v)
        (update_attribute_value o_l n_l)
        (update_attribute_value o_r n_r)
};

/**
 * Attribute tree evaluater(and updater) functions.
 */

let eval_binary binary parent_attribute => {
    let Attribute _  _  p_r = parent_attribute;
    switch binary {
        | Zero attribute => Zero (update_attribute attribute (Attribute (Some 0.) None p_r))
        | One attribute => One (update_attribute attribute (Attribute (square_some p_r) None p_r) )
    }
}; 
    
let rec eval_number1 number parent_attribute => {
    let Attribute _  _  p_r = parent_attribute;
    switch number {
        | N number binary attribute => {
            let attribute = update_attribute attribute (Attribute None None (add_one p_r));
            let new_binary = eval_binary binary attribute;
            let new_number = eval_number1 number attribute;

            let new_v = add_some (get_v (get_attribute_b new_binary)) (get_v (get_attribute_n new_number));
            let new_l = add_one (get_l (get_attribute_n new_number));
            let new_r = add_one p_r;
            let attribute = update_attribute attribute (Attribute new_v new_l new_r);
            N new_number new_binary attribute
        }
        | Lambda attribute => Lambda (update_attribute attribute (Attribute (Some 0.) (Some 0.) None))
    };
};

let rec eval_number2 number parent_attribute => {
    let Attribute _  _  p_r = parent_attribute;
    switch number {
        | N number binary attribute => {
            let Attribute _ l _ = attribute;
            let attribute = update_attribute attribute (Attribute None (negate_some l) (add_one p_r));
            let new_binary = eval_binary binary attribute;
            let new_number = eval_number2 number attribute;

            let new_v = add_some (get_v (get_attribute_b new_binary)) (get_v (get_attribute_n new_number));
            let new_l = add_one (get_l (get_attribute_n new_number));
            let new_r = negate_some new_l;
            let attribute = update_attribute attribute (Attribute new_v new_l new_r);
            N new_number new_binary attribute
        }
        | Lambda attribute => Lambda (update_attribute attribute (Attribute (Some 0.) (Some 0.) None))
    };
};

let rec eval start => 
    switch start {
        | S number1 dot number2 (Attribute (Some v) l r) => start
        | S number1 dot number2 attribute => {
            let n1 = eval_number1 number1 attribute; 
            let n2 = eval_number2 number2 attribute;
            let new_v = add_some (get_v (get_attribute_n n1)) (get_v (get_attribute_n n2));
            let attribute = update_attribute attribute (Attribute new_v None None);
            eval(S n1 dot n2 attribute) 
        };
    };

/**
 * Examples.
 */

let get_some_value = Option.value default::(-1.);

let initial_none = Attribute None None None;
let initial_n1 = Attribute None None (Some 0.);
let initial_n2 = initial_none;

let example1 = 
    (S 
        (N 
            (Lambda initial_none) 
            (One initial_none) 
            initial_n1) 
        Dot 
        (N 
            (Lambda initial_none) 
            (Zero initial_none) 
            initial_n2) 
        initial_none);

let example2 =
    (S 
        (N 
            (N 
                (Lambda initial_none) 
                (One initial_none) 
                initial_none) 
            (Zero initial_none) 
            initial_n1) 
        Dot 
        (N 
            (N
                (Lambda initial_none)
                (Zero initial_none)
                initial_none) 
            (One initial_none) 
            initial_n2) 
        initial_none);

let S _ _ _ (Attribute s_v1 _ _) = eval(example1);
Printf.printf "The result for example1: %F \n" (get_some_value s_v1);

let S _ _ _ (Attribute s_v2 _ _) = eval(example2);
Printf.printf "The result for example2: %F \n" (get_some_value s_v2);
