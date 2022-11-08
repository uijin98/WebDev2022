// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.13.0/firebase-app.js";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

import { 
    getAuth,// authentication 설정
    signInWithPopup, //google 로그인을 팝업창에 띄우기 위해
    GoogleAuthProvider, //google login 기능
    signInWithEmailAndPassword,// email 로그인
    createUserWithEmailAndPassword, //email 회원가입
} from 'https://www.gstatic.com/firebasejs/9.2.0/firebase-auth.js';


// Your web app's Firebase configuration
const firebaseConfig = {
apiKey: "AIzaSyA1IhyMtiCyPjCzgvwI7prkD9QK9NjIHas",
authDomain: "newearth-b3659.firebaseapp.com",
projectId: "newearth-b3659",
storageBucket: "newearth-b3659.appspot.com",
messagingSenderId: "109865594723",
appId: "1:109865594723:web:576164973901997fdf2d56"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);

// firebase의 인증객체를 받아둘 객체
const auth = firebase.auth();
// authoProvider를 GoogleAuthProvider를 이용한다.
var provider = new firebase.auth.GoogleAuthProvider();
//signInWithPopup(authProvider);

auth
.signInWithPopup(provider)
.then((result) => {
    /** @type {firebase.auth.OAuthCredential} */
    var credential = result.credential;

    // This gives you a Google Access Token. You can use it to access the Google API.
    var token = credential.accessToken;
    // The signed-in user info.
    var user = result.user;
    // ...
    console.log('success');
    console.log(user);
    console.log(user.uid);
    // userInfo = user;
    get_memo_list();
    console.log(data);
    

})
.catch((error) => {
    // Handle Errors here.
    var errorCode = error.code;
    var errorMessage = error.message;
    // The email of the user's account used.
    var email = error.email;
    // The firebase.auth.AuthCredential type that was used.
    var credential = error.credential;
    // ...
});