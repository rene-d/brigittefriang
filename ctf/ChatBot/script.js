const urlRegex = /([^\s]+:\/\/[^\s]+)/g;

String.prototype.escape = function() {
    var tagsToReplace = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;'
    };
    return this.replace(/[&<>]/g, function(tag) {
        return tagsToReplace[tag] || tag;
    });
};

function initBubbles(){
    var bubbles = [
        {
            text:"Bonjour"
        },
        {
            text:"Liste des emplois"
        }
        ,
        {
            text:"Comment candidater ?"
        }
    ];
    bubbles.forEach(function(bubble){
        $("#bubbles-container").append('<a href="" class="bubble-link"><div class="bubble rounded-lg py-2 px-4 mx-1 bg-grey">'+ bubble.text +'</div></a>');
    });
    return;
}

function urlify(text) {
    return text.replace(urlRegex, function (url) {
        return '<a href="' + url + '">' + url + '</a>';
    })
}

function addMessageUser(message,data) {
    if(data != null){
        $(".chat-message-list").append("\
        <div class='row mt-3 justify-content-end'> \
            <div class='col-auto'> \
                <div class='msg-1 rounded-sm'> \
                    " + message + " \
                    <hr>\
                    <div class='inline-block'>\
                        <img src='" + data.icon + "' style='max-width:20px;'> \
                        <p id='title'>"+ data.title + "</p> \
                    </div> \
                </div> \
            </div> \
        </div> \
    ");
    }
    else{
        $(".chat-message-list").append("\
        <div class='row mt-3 justify-content-end'> \
            <div class='col-auto'> \
                <p class='msg-1 rounded-sm '> \
                    " + message + " \
                </p> \
            </div> \
        </div> \
        ");
    }
    $(".messages").scrollTop($(".messages")[0].scrollHeight);
}

function addMessageContact(message,data) {
    if(data != null){
        $(".chat-message-list").append("\
        <div class='row mt-3'> \
            <div class='col-auto'> \
                <div class='msg-2 rounded-sm'> \
                    " + message + " \
                    <hr>\
                    <div class='inline-block'>\
                        <img src='" + data.icon + "'> \
                        <p id='title'>"+ data.title + "</p> \
                    </div> \
                </div> \
            </div> \
        </div> \
    ");
    }
    else{
        $(".chat-message-list").append("\
        <div class='row mt-3'> \
            <div class='col-auto'> \
                <p class='msg-2 rounded-sm'> \
                    " + message + " \
                </p> \
            </div> \
        </div> \
        ");
    }
    $(".messages").scrollTop($(".messages")[0].scrollHeight);
}

function askBot(message) {
    var url = window.location.href + "bot?message=" + message;
    fetch(url)
        .then(function (res) {
            res.json().then(function(data){
                var message = urlify(data.message)
                var urls = data.message.match(urlRegex);
                if (urls && urls.length > 0) {
                    var url = window.location.href + "proxy?url=" + urls[0];
                    fetch(url)
                        .then(function (res) {
                            console.log(res);
                            res.json()
                                .then(function (data) {
                                    if(data.err){
                                        addMessageContact(message,null);
                                    }
                                    else{
                                        addMessageContact(message,data);
                                    }
                                }).catch(function (err) {
                                    addMessageContact(message,null);
                                });
                        });
                } else {
                    addMessageContact(message,null);
                }
            });
        });
}

function sendFromInput(){
    var message = $("#input").val()
    console.log(message)
    send(message);
    $("#input").val("");
    return;
}

function send(mess) {
    var message = urlify(mess);
    var urls = mess.match(urlRegex);
    if(message.length <= 0){
        return;
    }
    //If URL
    if (urls && urls.length > 0) {
        var url = window.location.href + "proxy?url=" + urls[0];
        fetch(url)
            .then(function (res) {
                console.log(res);
                res.json()
                    .then(function (data) {
                        if(data.err){
                            addMessageUser(message,null);
                            askBot(mess);
                        }
                        else{
                            addMessageUser(message,data);
                            askBot(mess);
                        }
                    }).catch(function (err) {
                        addMessageUser(message,null);
                        askBot(mess);
                    });
            });
    } else {
        addMessageUser(message,null);
        askBot(mess);
    }
}

$(document).ready(function () {
    initBubbles();
    $('#input').bind("enterKey", function (e) {
        sendFromInput();
    });
    $('#input').keyup(function (e) {
        if (e.keyCode == 13) {
            $(this).trigger("enterKey");
        }
    });
    $('.bubble').click(function (e) {
        e.preventDefault();
        var text = $(this).first().text();
        console.log(text);
        send(text);
    });
    askBot("Bonjour");
});