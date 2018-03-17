// HIGHER ORDER COMPONENT (HOC)
// A component that renders another componet

import React from 'react';
import ReactDOM from 'react-dom';

const Info = (props) => (
    <div>
        <h1>Info</h1>
        <p>The info is: {props.info}</p>
    </div>
);

const withAdminWarning = (WrappedComponent) => {
    // HOC
    return (props) => (
        <div>
            {props.isAdmin && <p>This is private info, please don't share</p>}
            <WrappedComponent {...props}/>
        </div>
    );
};

const requireAuth = (WrappedComponent) => {
    // HOC
    return (props) => (
        <div>
            {props.isAuth
                    ?
                    (<WrappedComponent {...props} />)
                    :
                    (<p>Please Login to view the Info</p>)
            }
        </div>
    );
};

const AdminInfo = withAdminWarning(Info);
const AuthInfo = requireAuth(Info);

// ReactDOM.render(<AdminInfo isAdmin={false} info="This are the details" />,
//     document.getElementById('app'));
ReactDOM.render(<AuthInfo isAuth={false} info="This are the details" />,
    document.getElementById('app'));
