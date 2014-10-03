-module(agdyne_main).
-behavior(gen_server).
-export([init/1, terminate/2,
         handle_call/3, handle_cast/2, handle_info/2
        ]).

%% gen_server behaviors
init(_) -> {ok, nil}.

terminate(Reason, State) -> {Reason, State}.

handle_call(Request, Form, State) ->
    Request, Form, State = Request, Form, State,
    {reply, Request, State}.

