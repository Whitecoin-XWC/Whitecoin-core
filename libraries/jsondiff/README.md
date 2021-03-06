jsondiff-cpp
=================

Diff & patch json implemented by C++

# Dependencies

* boost 1.55
* https://github.com/cryptonomex/fc

# Features

* diff json
* patch jsondiff to old version json, generate new version json
* rollback from new version json to old version json, using diff-json generated before

# Design

* support types: number, boolean, string, null, object, array
* diff design

```
    colorize(for pretty print)
		✓ should return ' <value>' for a scalar value
		✓ should return '-<old value>', '+<new value>' for a scalar diff
		✓ should return '-<removed key>: <removed value>' for an object diff with a removed key
		✓ should return '+<added key>: <added value>' for an object diff with an added key
		✓ should return '+<added key>: <added stringified value>' for an object diff with an added key and a non-scalar value
		✓ should return ' <modified key>: <colorized diff>' for an object diff with a modified key
		✓ should return '+<inserted item>' for an array diff
		✓ should return '-<deleted item>' for an array diff
    diff
	  with simple scalar values or different type values
		✓ should return undefined for two identical values
		✓ should return { __old: <old value>, __new: <new value> } object for two different numbers
	  with objects(both old and new values are objects)
		✓ should return undefined for two objects with identical contents
		✓ should return undefined for two object hierarchies with identical contents
		✓ should return { <key>__deleted: <old value> } when the second object is missing a key
		✓ should return { <key>__added: <new value> } when the first object is missing a key
		✓ should return { <key>: { __old: <old value>, __new: <new value> } } for two objects with diffent scalar values for a key
		✓ should return { <key>: <diff> } with a recursive diff for two objects with diffent values for a key
	  with arrays of scalars
		✓ should return undefined for two arrays with identical contents
		✓ should return [..., ['-', remove_from_position_index, <removed item>], ...] for two arrays when the second array is missing a value
		✓ should return [..., ['+', insert_position_index, <added item>], ...] for two arrays when the second one has an extra value
		✓ should return [..., ['+', insert_position_index, <added item>]] for two arrays when the second one has an extra value at the end (edge case test)
	  with arrays of objects
		✓ should return undefined for two arrays with identical contents
		✓ should return [..., ['-', remove_from_position_index, <removed item>], ...] for two arrays when the second array is missing a value
		✓ should return [..., ['+', insert_position_index, <added item>], ...] for two arrays when the second array has an extra value
		✓ should return [..., ['~', position_index, <diff>], ...] for two arrays when an item has been modified (note: involves a crazy heuristic)

```

# Usage

```

	{
		JsonDiff json_diff;
		auto origin = R"({
  "foo": 42,
  "bar": 100,
  "boz": [
    1,
    2,
    3,
    4,
    5,
    6
  ],
  "array": [1,2,3,4,5,6],
  "fubar": {
    "kaboom": {
      "note": "We're running dangerously low on metasyntatic variables here",
      "afoo": {
        "abar": "raba",
        "aboz": "zoba",
        "afubar": "rabufa"
      },
      "akaboom": 200
    }
  }
})";
		auto result = R"({
  "foo": 42,
  "bar": 100,
  "boz": {
      "a":[1,2,3]
  },
  "array": [0, 1,3,4,6,7,5],
  "fubar": {
    "kaboom": {
      "note": "We're running dangerously low on metasyntatic variables here",
      "afoo": {
        "abar": "raba",
        "aboz": "zozoba",
        "afubar": "rabufa",
        "c": 123
      },
      "akaboom": 200
    }
  }
})";
		auto diff_result = json_diff.diff_by_string(std::string(origin), std::string(result));
		auto diff_result_str = diff_result->pretty_str();
		auto diff_result_pretty_str = diff_result->pretty_diff_str();
		std::cout << "diff: " << std::endl << diff_result_str << std::endl;
		/*
		output:
		diff:
		{
		  "boz": {
			"__old": [
			  1,
			  2,
			  3,
			  4,
			  5,
			  6
			],
			"__new": {
			  "a": [
				1,
				2,
				3
			  ]
			}
		  },
		  "array": [[
			  "~",
			  0,{
				"__old": 1,
				"__new": 0
			  }
			],[
			  "~",
			  1,{
				"__old": 2,
				"__new": 1
			  }
			],[
			  "~",
			  4,{
				"__old": 5,
				"__new": 6
			  }
			],[
			  "~",
			  5,{
				"__old": 6,
				"__new": 7
			  }
			],[
			  "+",
			  6,
			  5
			]
		  ],
		  "fubar": {
			"kaboom": {
			  "afoo": {
				"aboz": {
				  "__old": "zoba",
				  "__new": "zozoba"
				},
				"c__added": 123
			  }
			}
		  }
		}
		*/
		std::cout << "diff pretty: " << std::endl << diff_result_pretty_str << std::endl;
		/*
		output:
		diff pretty:
        boz:
        -[1,2,3,4,5,6]
        +{"a":[1,2,3]}

        array:
                ~
                -1
                +0

                ~
                -2
                +1

                ~
                -5
                +6

                ~
                -6
                +7

                +5

        fubar:
                kaboom:
                        afoo:
                                aboz:
                                -"zoba"
                                +"zozoba"

                                +c:123
		*/
		auto patched = json_diff.patch_by_string(origin, diff_result);
		std::cout << "patched: " << json_dumps(patched) << std::endl;
		/*
		output:
		patched: {"foo":42,"bar":100,"boz":{"a":[1,2,3]},"array":[0,1,3,4,6,7,5],"fubar"
		:{"kaboom":{"note":"We're running dangerously low on metasyntatic variables here",
		"afoo":{"abar":"raba","aboz":"zozoba","afubar":"rabufa","c":123},"akaboom":200}}}
		*/
		assert(json_dumps(patched) == json_dumps(json_loads(result)));

		auto rollbacked = json_diff.rollback_by_string(result, diff_result);
		std::cout << "rollbacked: " << json_dumps(rollbacked) << std::endl;
		/*
		output:
		rollbacked: {"foo":42,"bar":100,"boz":[1,2,3,4,5,6],"array":[1,2,3,4,5,6],"fubar":
		{"kaboom":{"note":"We're running dangerously low on metasyntatic variables here",
		"afoo":{"abar":"raba","aboz":"zoba","afubar":"rabufa"},"akaboom":200}}}	
		*/
		assert(json_dumps(rollbacked) == json_dumps(json_loads(origin)));
	}

```